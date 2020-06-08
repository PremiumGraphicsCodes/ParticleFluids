#include "FluidSimulator.h"

#include "SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Algo::Physics;

void MacroParticle::distributePoints(const int unum, const int vnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;
	for (double x = 0.0; x <= 1.0 + tolerance; x += dx) {
		for (double y = 0.0; y < 1.0 + tolerance; y += dy) {
			points.push_back(new MicroParticle(Vector3dd(x, y, 0.0)));
		}
	}
}

void MacroParticle::calculateDensity()
{
	(innerPoints.size() - points.size() ) / points.size();
}

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

}


void FluidSimulator::simulate(const double dt)
{
	calculateDensity();

}
