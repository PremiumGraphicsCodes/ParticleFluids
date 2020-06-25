#include "FluidSimulator.h"

#include "FluidScene.h"
#include "SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::Physics;

FluidSimulator::FluidSimulator() :
	timeStep(0.01)
{}

void FluidSimulator::step()
{
	simulate(timeStep);
}

void FluidSimulator::simulate(const double dt)
{
	std::vector<MacroParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	for (auto particle : particles) {
		particle->reset();
	}

	SpaceHash spaceHash(particles.front()->getRadius() * 1.5, static_cast<int>(particles.size()));
	for (auto particle : particles) {
		spaceHash.add(particle);
	}

#pragma omp parallel for
	for(int i = 0; i < particles.size(); ++i) {
		const auto particle = particles[i];
		const auto& microParticles = particle->getPoints();
		for (auto mp : microParticles) {
			spaceHash.getNeighbors(mp, particle);
		}
//	for (auto particle : particles) {
//		const auto& position = particle->getPosition();
//		auto neighbors = spaceHash.getNeighbors(position, particle);
//		neighbors.sort();
//		neighbors.unique();
//		particle->setInnerPoints(neighbors);
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
		if (position.x > 20.0) {
			const auto overlap = Vector3dd(20.0 - position.x, 0, 0);
			particle->addForce(overlap / dt / dt);
		}
		if (position.x < -20.0) {
			const auto overlap = Vector3dd(-20.0 - position.x, 0, 0);
			particle->addForce(overlap / dt / dt);
		}
		if (position.z > 20.0) {
			const auto overlap = Vector3dd(0, 0, 20.0 - position.z);
			particle->addForce(overlap / dt / dt);
		}
		if (position.z < -20.0) {
			const auto overlap = Vector3dd(0, 0, -20.0 - position.x);
			particle->addForce(overlap / dt / dt);
		}



	}

	for (auto particle : particles) {
		particle->addForce(Vector3dd(0.0,-9.8,0.0));
		particle->stepTime(dt);
	}

	for (auto fluid : fluids) {
		fluid->getController()->updateView();
	}

}
