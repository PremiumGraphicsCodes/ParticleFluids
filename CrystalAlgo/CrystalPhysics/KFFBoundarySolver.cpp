#include "KFFBoundarySolver.h"

#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void KFFBoundarySolver::solve(MacroParticle* particle, const double dt)
{
	auto position = particle->getPosition();
	if (position.y < boundary.getMinY()) {
		const auto distance = boundary.getMinY() - position.y;
		/*
		MacroParticle* mp = new MacroParticle(particle->getRadius(), Vector3dd(position.x, 0.0, position.z));
		mp->distributePoints(5, 5, 5);
		boundaryParticles.push_back(mp);
		particle->addMicro()
		*/
		const auto overlap = Vector3dd(0, distance, 0);
		const auto count = (distance) / (particle->getRadius() * 0.1);
		particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}
	if (position.x > boundary.getMaxX()) {
		const auto distance = boundary.getMaxX() - position.x;
		const auto overlap = Vector3dd(distance, 0, 0);
		const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
		particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}
	if (position.x < boundary.getMinX()) {
		const auto distance = boundary.getMinX() - position.x;
		const auto overlap = Vector3dd(distance, 0, 0);
		const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
		particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}
	if (position.z > boundary.getMaxZ()) {
		const auto distance = boundary.getMaxZ() - position.z;
		const auto overlap = Vector3dd(0, 0, distance);
		const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
		particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}
	if (position.z < boundary.getMinZ()) {
		const auto distance = boundary.getMinZ() - position.z;
		const auto overlap = Vector3dd(0, 0, distance);
		const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
		particle->addBoundaryCount(count * 10);
		particle->addForce(overlap / dt / dt);
	}

}

void KFFBoundarySolver::createMacro(const Vector3dd& position)
{

}