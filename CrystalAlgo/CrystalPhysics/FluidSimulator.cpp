#include "FluidSimulator.h"

#include "../CrystalAlgo/SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::Physics;

void FluidSimulator::calculateDensity()
{
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
}

void FluidSimulator::calculatePressure()
{
	for (auto particle : particles) {
		particle->calculatePressure();
	}
}

void FluidSimulator::calculateViscosity()
{
	for (auto particle : particles) {
		particle->calculateViscosity();
	}
}

void FluidSimulator::simulate(const double dt)
{
	calculateDensity();
	calculatePressure();
	calculateViscosity();
}
