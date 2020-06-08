#include "FluidSimulator.h"

#include "FluidScene.h"
#include "../CrystalAlgo/SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::Physics;


void FluidSimulator::simulate(const double dt)
{
	std::list<MacroParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	SpaceHash spaceHash(particles.front()->getRadius() * 2.0, static_cast<int>(particles.size()));
	for (auto particle : particles) {
		const auto& points = particle->getPoints();
		for (auto point : points) {
			spaceHash.add(point);
		}
	}

	for (auto particle : particles) {
		const auto& position = particle->getPosition();
		const auto& neighbors = spaceHash.getNeighbors(position);
		particle->setInnerPoints(neighbors);
	}

	for (auto particle : particles) {
		particle->calculatePressure();
	}

	for (auto particle : particles) {
		particle->calculateViscosity();
	}

	for (auto particle : particles) {
		particle->addForce(Vector3dd(0.0,-9.8,0.0));
		particle->stepTime(dt);
	}
}
