#include "KFFBoundarySolver.h"

#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void KFFBoundarySolver::solve(MacroParticle* particle, const double dt)
{
	auto position = particle->getPosition();
	if (position.y < boundary.getMinY()) {
		const auto distance = boundary.getMinY() - position.y;
		const auto overlap = Vector3dd(0, distance, 0);
		const auto count = (distance) / (particle->getRadius() * 0.1);
		particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}
	if (position.x > boundary.getMaxX()) {
		const auto distance = boundary.getMaxX() - position.x;
		const auto overlap = Vector3dd(distance, 0, 0);
		const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
		//particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}
	if (position.x < boundary.getMinX()) {
		const auto distance = boundary.getMinX() - position.x;
		const auto overlap = Vector3dd(distance, 0, 0);
		const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
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

void KFFBoundarySolver::createMacro(MacroParticle* mp)
{
	const auto position = mp->getPosition();
	const auto radius = mp->getRadius();
	if (position.y < boundary.getMinY() + radius * 2.0) {
		auto bp = std::make_unique<MacroParticle>(radius, position);
		const Vector3dd p1(position.x, boundary.getMinY() + radius, position.z);
		const Vector3dd p2(position.x, boundary.getMinY(), position.z);
		createMacro(mp, p1);
		createMacro(mp, p2);
	}
}

void KFFBoundarySolver::createMacro(MacroParticle* mp, const Vector3dd& position)
{
	auto bp = std::make_unique<MacroParticle>(mp->getRadius(), position);
	const auto radius = mp->getRadius() * 2.0;

	const int unum = 3;
	const int vnum = 3;
	const int wnum = 3;
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
//			for (int z = 0; z <= wnum; ++z) {
				const auto xx = x / (double)unum;
				const auto yy = y / (double)vnum;
//				const auto zz = z / (double)wnum;
				const Vector3dd v(xx - 0.5, yy - 0.5, 0.0);// zz - 0.5);
				auto micro = new MicroParticle(mp, v * 2.0, 1.0);
				if (Math::getDistanceSquared(micro->getPosition(), mp->getPosition()) < radius * radius) {
					mp->addMicro(micro);
					bp->addSelfMicro(micro);
				}
			}
//		}
	}

	//macro->addMicro()
	macros.push_back(std::move(bp));
}