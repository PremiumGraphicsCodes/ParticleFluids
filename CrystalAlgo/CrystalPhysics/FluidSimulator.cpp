#include "FluidSimulator.h"

#include "FluidScene.h"
#include "../CrystalAlgo/SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::Physics;

FluidSimulator::FluidSimulator()
{}

void FluidSimulator::step()
{
	simulate(timeStep);
}

void FluidSimulator::simulate(const double dt)
{
	std::list<MacroParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	for (auto particle : particles) {
		particle->reset();
	}

	SpaceHash spaceHash(particles.front()->getRadius(), static_cast<int>(particles.size()));
	for (auto particle : particles) {
		const auto& points = particle->getPoints();
		for (auto point : points) {
			spaceHash.add(point);
		}
	}

	for (auto particle : particles) {
		const auto& position = particle->getPosition();
		auto neighbors = spaceHash.getNeighbors(position);
		neighbors.sort();
		neighbors.unique();
		particle->setInnerPoints(neighbors);
	}

	for (auto particle : particles) {
		particle->calculatePressure();
	}

	/*
	for (auto particle : particles) {
		particle->calculateViscosity();
	}
	*/

	for (auto particle : particles) {
		particle->addForce(Vector3dd(0.0,-9.8,0.0));
		particle->stepTime(dt);
	}

	for (auto fluid : fluids) {
		fluid->getController()->updateView();
	}

}
