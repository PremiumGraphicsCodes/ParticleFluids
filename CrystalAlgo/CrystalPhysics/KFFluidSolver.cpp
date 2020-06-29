#include "KFFluidSolver.h"

#include "MicroParticle.h"
#include "MacroParticle.h"

#include "KFFluidScene.h"
#include "../CrystalAlgo/SpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Search;
using namespace Crystal::Physics;

KFFluidSolver::KFFluidSolver() :
	timeStep(0.01)
{}

void KFFluidSolver::step()
{
	simulate(timeStep);
}

void KFFluidSolver::simulate(const double dt)
{
	std::vector<MacroParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	for (auto particle : particles) {
		particle->reset();
	}

	SpaceHash3d spaceHash(particles.front()->getRadius() * 1.25, static_cast<int>(particles.size() * 10));
	for (auto particle : particles) {
		spaceHash.add(particle);
	}

	auto func = [](Shape::IPoint* macro, Shape::IPoint* micro) {
		MacroParticle* mp = static_cast<MacroParticle*>(macro);
		MicroParticle* microP = static_cast<MicroParticle*>(micro);
		mp->addMicro(microP);
	};
	//						p->addMicro(micro);


#pragma omp parallel for
	for(int i = 0; i < particles.size(); ++i) {
		const auto particle = particles[i];
		const auto& microParticles = particle->getPoints();
		for (auto mp : microParticles) {
			spaceHash.solveInteractions(mp, func);
		}
	}

	for (auto particle : particles) {
		particle->calculatePressure(particle->getScene()->getPressureCoe());
	}

	for (auto particle : particles) {
		particle->calculateViscosity(particle->getScene()->getViscosityCoe());
	}

	for (auto particle : particles) {
		auto position = particle->getPosition();
		if (position.y < boundary.getMinY()) {
			const auto distance = boundary.getMinY() - position.y;
			const auto overlap = Vector3dd(0, distance, 0);
			const auto count = (distance) / (particle->getRadius() * 0.1);
			particle->addMicroCount(count * 10);
			particle->addForce( overlap / dt / dt );
		}
		if (position.x > boundary.getMaxX()) {
			const auto overlap = Vector3dd(boundary.getMaxX() - position.x, 0, 0);
			particle->addForce(overlap / dt / dt);
		}
		if (position.x < boundary.getMinX()) {
			const auto overlap = Vector3dd(boundary.getMinX() - position.x, 0, 0);
			particle->addForce(overlap / dt / dt);
		}
		if (position.z > boundary.getMaxZ()) {
			const auto overlap = Vector3dd(0, 0, boundary.getMaxZ() - position.z);
			particle->addForce(overlap / dt / dt);
		}
		if (position.z < boundary.getMinZ()) {
			const auto overlap = Vector3dd(0, 0, boundary.getMinZ() - position.z);
			particle->addForce(overlap / dt / dt);
		}
	}

	for (auto particle : particles) {
		particle->addForce(Vector3dd(0.0,-9.8 * particle->getDensity(),0.0));
		particle->stepTime(dt);
	}

	// solve incompressibility.
	double relaxationCoe = 0.5;
	for (int i = 0; i < 2; ++i) {
		for (auto particle : particles) {
			particle->reset();
		}

#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto particle = particles[i];
			const auto& microParticles = particle->getPoints();
			for (auto mp : microParticles) {
				spaceHash.solveInteractions(mp, func);
			}
		}

		for (auto particle : particles) {
			particle->calculatePressure(particle->getScene()->getPressureCoe() * relaxationCoe);
			//particle->calculateViscosity(particle->getScene()->getViscosityCoe() * relaxationCoe);
			particle->stepTime(dt);
		}
		relaxationCoe /= 2.0;
	}

	for (auto fluid : fluids) {
		fluid->getController()->updateView();
	}

}
