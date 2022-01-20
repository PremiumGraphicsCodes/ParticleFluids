#include "MVPFluidSolver.h"

#include "MVPMassParticle.h"
#include "MVPVolumeParticle.h"

#include "MVPFluidScene.h"
#include "MVPFluidEmitterScene.h"
#include "../CSGBoundaryScene.h"

#include "../../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"
#include "../MVPSurfaceBuilder.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

MVPFluidSolver::MVPFluidSolver() :
	externalForce(0.0, -9.8f, 0.0)
{}

MVPFluidSolver::MVPFluidSolver(const int id) :
	IAnimator(id),
	externalForce(0.0, -9.8f, 0.0)
{}

void MVPFluidSolver::setupBoundaries()
{
	this->boundarySolver.setup(effectLength);
}

void MVPFluidSolver::clear()
{
	fluids.clear();
	emitters.clear();
	csgBoundaries.clear();
	maxTimeStep = 0.03f;
	boundarySolver.clear();
	currentTimeStep = 0;
}

void MVPFluidSolver::addFluidScene(MVPFluidScene* scene)
{
	this->fluids.push_back(scene);
}

void MVPFluidSolver::addEmitterScene(MVPFluidEmitterScene* scene)
{
	this->emitters.push_back(scene);
}

void MVPFluidSolver::addBoundaryScene(MVPFluidScene* scene)
{
	this->boundarySolver.addBoundaryScene(scene);
}

void MVPFluidSolver::step()
{
	simulate();
}

void MVPFluidSolver::simulate()
{
	std::vector<MVPMassParticle*> massParticles;

	for (auto emitter : emitters) {
		emitter->emitParticle(currentTimeStep);
		const auto ps = emitter->getParticles();
		massParticles.insert(massParticles.end(), ps.begin(), ps.end());
	}

	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		massParticles.insert(massParticles.end(), ps.begin(), ps.end());
	}

	if (massParticles.empty()) {
		currentTimeStep++;
		return;
	}

	std::vector<MVPVolumeParticle*> fluidParticles;
	{
		const auto leafSize = effectLength * 1.0;
		CompactSpaceHash3d spaceHash(leafSize, massParticles.size());
		for (auto p : massParticles) {
			spaceHash.add(p);
		}
		const auto cells = spaceHash.getCells();

		for (auto c : cells) {
			Vector3dd center(0, 0, 0);
			Vector3dd velocity(0, 0, 0);
			for (auto p : c->particles) {
				auto mp = static_cast<MVPMassParticle*>(p);
				center += p->getPosition();
				velocity += mp->getVelocity();
			}
			center /= static_cast<float>(c->particles.size());
			velocity /= static_cast<float>(c->particles.size());
			MVPVolumeParticle* vp = new MVPVolumeParticle(leafSize * 2.0, center);
			for (auto p : c->particles) {
				auto mp = static_cast<MVPMassParticle*>(p);
				mp->setParent(vp);
				vp->addMassParticle(mp);
			}
			vp->setVelocity(velocity);
			fluidParticles.push_back(vp);			
			vp->setRestMass(massParticles.front()->getMass() * 8.0);
			vp->reset(false);
		}
		for (auto p : massParticles) {
			assert(p->getParent() != nullptr);
		}
	}

	const auto hashSize = fluidParticles.size();
	const auto searchRadius = effectLength;
	CompactSpaceHash3d spaceHash(searchRadius, static_cast<int>( hashSize));
	for (auto particle : fluidParticles) {
		spaceHash.add(particle);
	}

	//boundarySolver.setup(searchRadius);

#pragma omp parallel for
	for(int i = 0; i < fluidParticles.size(); ++i) {
		const auto particle = fluidParticles[i];
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto n : neighbors) {
			particle->addNeighbor(static_cast<MVPVolumeParticle*>(n));
		}
		const auto staticNeighbors = boundarySolver.findNeighbors(particle->getPositionf());
		for (auto n : staticNeighbors) {
			particle->addNeighbor(static_cast<MVPVolumeParticle*>(n));
		}
	}

	double time = 0.0;
	while (time < maxTimeStep) {
		const auto dt = calculateTimeStep(fluidParticles);

		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateMassPositions();
			particle->updateMassVelocities();
		}

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateInnerPoints();
			particle->calculateDensity();
			particle->calculateViscosityForce();
			//particle->calculateVorticity();
		}
		

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			//boundarySolver.createMacro(particle);
			solveBoundary(particle, dt);
		}

		for (auto particle : fluidParticles) {
			particle->addForce(externalForce * particle->getDensity());
			//particle->stepTime(dt);
		}

		// solve incompressibility.
		double relaxationCoe = 1.0;
		for (int i = 0; i < 3; ++i) {
			for (auto particle : fluidParticles) {
//				particle->reset(false);
				particle->updateMassPositions();
			}

#pragma omp parallel for
			for (int i = 0; i < fluidParticles.size(); ++i) {
				const auto particle = fluidParticles[i];
				particle->updateInnerPoints();
				//particle->calculateDensity();
				particle->calculatePressureForce(relaxationCoe, dt);
			}
			relaxationCoe *= 0.85;


			//for (auto particle : fluidParticles) {
			//	solveBoundary(particle, dt);
			//}
			//	solveBoundary(particles);
		}

		for (auto particle : fluidParticles) {
			//particle->calculateViscosity(particle->getScene()->getViscosityCoe() * relaxationCoe);
			particle->stepTime(dt);
			/*
			const auto massPs = particle->getMassParticles();
			for (auto mp : massPs) {
				mp->updateVector(dt);
			}
			*/
		}

		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : fluidParticles) {
		densityError += particle->getDensity() / (double)fluidParticles.size();
	}
	std::cout << densityError << std::endl;

	for (auto vp : fluidParticles) {
		delete vp;
	}

	/*
	for (auto f : fluids) {
		const auto fps = f->getParticles();
		std::vector<MVPVolumeParticle*> ps;
		for (auto p : fps) {
			if (p->getDensity() < 0.75) {
				ps.push_back(p);
			}
		}
		for (auto p : ps) {
			const auto masses = p->getMassParticles();
			for (auto m : masses) {
				MVPVolumeParticle* vp = new MVPVolumeParticle(p->getRadius() * 0.50, m->getPosition());
				vp->setVelocity(m->getVelocity());
				vp->addMassParticle(m);
				m->setParent(vp);
				vp->setRestMass(m->getMass());
				f->add(vp);
			}
			p->clearMasses();
			f->remove(p);
			delete p;
		}
	}

	for (auto f : fluids) {
		const auto fps = f->getParticles();
		for (auto p : fps) {
			if (p->getDensity() > 1.5) {
				const auto ns = p->getNeighbors();
				for (auto n : ns) {
					const auto mps = p->getMassParticles();
					if (mps.size() < 8) {
						for (auto m : mps) {
							p->addMassParticle(m);
							m->setParent(
						}
					}
				}
			}
		}

	}
	*/

	currentTimeStep++;
}

float MVPFluidSolver::calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles)
{
	float maxVelocity = 0.0f;
	for (auto p : particles) {
		maxVelocity = std::max<float>(maxVelocity, Math::getLengthSquared( p->getVelocity() ) );
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4f * particles.front()->getRadius() * 2.0f / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}

void MVPFluidSolver::solveBoundary(MVPVolumeParticle* particle, const double dt)
{
	for (const auto& csg : csgBoundaries) {
		for (const auto& boundary : csg->getBoxes()) {
			auto position = particle->getPosition();
			if (position.y < boundary.getMinY()) {
				const auto distance = boundary.getMinY() - position.y;
				const auto overlap = Vector3dd(0, distance, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.y > boundary.getMaxY()) {
				const auto distance = boundary.getMaxY() - position.y;
				const auto overlap = Vector3dd(0, distance, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.x > boundary.getMaxX()) {
				const auto distance = boundary.getMaxX() - position.x;
				const auto overlap = Vector3dd(distance, 0, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.x < boundary.getMinX()) {
				const auto distance = boundary.getMinX() - position.x;
				const auto overlap = Vector3dd(distance, 0, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z > boundary.getMaxZ()) {
				const auto distance = boundary.getMaxZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z < boundary.getMinZ()) {
				const auto distance = boundary.getMinZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				particle->addForce(overlap / dt / dt);
			}
		}
	}
}

void MVPUpdater::step()
{
	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
		//for(auto b : fluid->get)
	}
	//for(auto b : csgB)
}
