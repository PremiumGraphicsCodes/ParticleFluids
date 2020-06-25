#include "KFFluidSolver.h"

#include "MicroParticle.h"
#include "MacroParticle.h"

#include "FluidScene.h"
#include "SpaceHash.h"

using namespace Crystal::Math;
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

	SpaceHash spaceHash(particles.front()->getRadius() * 1.25, static_cast<int>(particles.size()));
	for (auto particle : particles) {
		spaceHash.add(particle);
	}

#pragma omp parallel for
	for(int i = 0; i < particles.size(); ++i) {
		const auto particle = particles[i];
		const auto& microParticles = particle->getPoints();
		for (auto mp : microParticles) {
			spaceHash.getNeighbors(mp);
		}
	}

	for (auto particle : particles) {
		particle->calculatePressure();
	}

	for (auto particle : particles) {
		particle->calculateViscosity();
	}

	for (auto particle : particles) {
		auto position = particle->getPosition();
		if (position.y < 0.0) {
			const auto overlap = Vector3dd(0, -position.y, 0);
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

	for (auto fluid : fluids) {
		fluid->getController()->updateView();
	}

}
