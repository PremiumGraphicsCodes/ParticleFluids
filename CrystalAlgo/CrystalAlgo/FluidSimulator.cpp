#include "FluidSimulator.h"

#include "SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;

void MacroParticle::distributePoints(const int unum, const int vnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;
	for (double x = 0.0; x <= 1.0; x += dx) {
		for (int j = 0; j < 10; ++j) {

		}
	}
}

void MacroParticle::calculateDensity()
{
	points.size();
}

void FluidSimulator::calculateDensity()
{
	SpaceHash spaceHash(particles.front()->getRadius(), static_cast<int>(particles.size()));
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

}


void FluidSimulator::simulate(const double dt)
{
	calculateDensity();

}
