#include "MVPFluidSolver.h"

#include "MVPMassParticle.h"
#include "MVPVolumeParticle.h"

#include "MVPFluidScene.h"
#include "MVPFluidEmitterScene.h"
#include "../CSGBoundaryScene.h"

#include "../../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPBoundarySolver::setup(const float effectLength)
{
	std::vector<MVPVolumeParticle*> boundaryParticles;
	for (auto b : boundaries) {
		const auto bp = b->getParticles();
		boundaryParticles.insert(boundaryParticles.end(), bp.begin(), bp.end());
	}

	if (boundaryParticles.empty()) {
		return;
	}

	const auto hashSize = boundaryParticles.front()->getPoints().size() * boundaryParticles.size();
	const auto searchRadius = effectLength;
	spaceHash = std::make_unique<CompactSpaceHash3d>(searchRadius, boundaryParticles.size());
	//spaceHash.setup(searchRadius, boundaryParticles.size());

	for (auto bp : boundaryParticles) {
		const auto& microParticles = bp->getPoints();
		for (auto mp : microParticles) {
			spaceHash->add(mp);
		}
	}
}

std::vector<IParticle*> MVPBoundarySolver::findNeighbors(const Vector3dd& position)
{
	if (spaceHash == nullptr) {
		return {};
	}
	return spaceHash->findNeighbors(position);
}

MVPFluidSolver::MVPFluidSolver(const int id) :
	IAnimator(id)
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
	std::vector<MVPVolumeParticle*> fluidParticles;

	for (auto emitter : emitters) {
		emitter->emitParticle(currentTimeStep);
		const auto ps = emitter->getParticles();
		fluidParticles.insert(fluidParticles.end(), ps.begin(), ps.end());
	}

	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		fluidParticles.insert(fluidParticles.end(), ps.begin(), ps.end());
	}

	for (auto particle : fluidParticles) {
		particle->reset(true);
	}

	if (fluidParticles.empty()) {
		currentTimeStep++;
		return;
	}

	const auto hashSize = fluidParticles.front()->getPoints().size() * fluidParticles.size();
	const auto searchRadius = effectLength;
	CompactSpaceHash3d spaceHash(searchRadius, static_cast<int>( hashSize));
	for (auto particle : fluidParticles) {
		particle->updateMicros();
		const auto& microParticles = particle->getPoints();
		for (auto mp : microParticles) {
			spaceHash.add(mp);
		}
	}

#pragma omp parallel for
	for(int i = 0; i < fluidParticles.size(); ++i) {
		const auto particle = fluidParticles[i];
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto n : neighbors) {
			particle->addMicro(static_cast<MVPMassParticle*>(n));
		}
		const auto& bps = boundarySolver.findNeighbors(particle->getPosition());
		for (auto n : bps) {
			particle->addMicro(static_cast<MVPMassParticle*>(n));
		}
	}

	double time = 0.0;
	while (time < maxTimeStep) {
		const auto dt = calculateTimeStep(fluidParticles);

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateInnerPoints();
			particle->calculateDensity();
			particle->calculatePressure();
			particle->calculatePressureForce(1.0);
			particle->calculateViscosityForce();
		}
		

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			//boundarySolver.createMacro(particle);
			solveBoundary(particle, dt);
		}

		for (auto particle : fluidParticles) {
			particle->addForce(Vector3dd(0.0, -9.8 * particle->getDensity(), 0.0));
			particle->stepTime(dt);
		}

		// solve incompressibility.
		float relaxationCoe = 0.5f;
		for (int i = 0; i < 2; ++i) {
			for (auto particle : fluidParticles) {
				particle->reset(false);
				particle->updateMicros();
			}

#pragma omp parallel for
			for (int i = 0; i < fluidParticles.size(); ++i) {
				const auto particle = fluidParticles[i];
				particle->updateInnerPoints();
				particle->calculateDensity();
				particle->calculatePressure();
				particle->calculatePressureForce(relaxationCoe);
			}

			for (auto particle : fluidParticles) {
				solveBoundary(particle, dt);
			}
			//	solveBoundary(particles);

			for (auto particle : fluidParticles) {
				//particle->calculateViscosity(particle->getScene()->getViscosityCoe() * relaxationCoe);
				particle->stepTime(dt);
			}
			relaxationCoe /= 2.0;
		}

		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : fluidParticles) {
		densityError += particle->getDensity() / (double)fluidParticles.size();
	}
	std::cout << densityError << std::endl;


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
				//const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
				//particle->addBoundaryCount(count * 10);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z > boundary.getMaxZ()) {
				const auto distance = boundary.getMaxZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
				//particle->addBoundaryCount(count * 10);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z < boundary.getMinZ()) {
				const auto distance = boundary.getMinZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
				//particle->addBoundaryCount(count * 10);
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