#include "SPHFlameBoundarySolver.h"

#include "SPHFlameParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

SPHFlameBoundarySolver::SPHFlameBoundarySolver(const float timeStep, const Box3dd& boundary) :
	timeStep(timeStep),
	boundary(boundary)
{
}

void SPHFlameBoundarySolver::solve(const std::vector<SPHFlameParticle*>& particles) {
#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		const auto force = getBoundaryForce(particles[i]->getPosition());
		particles[i]->addForce(force * particles[i]->getDensity());
	}
}

Vector3df SPHFlameBoundarySolver::getBoundaryForce(const Vector3df& center)
{
	Math::Vector3df force(0, 0, 0);

	force += getForceX(center.x);
	force += getForceY(center.y);
	force += getForceZ(center.z);

	return force;
}

Vector3df SPHFlameBoundarySolver::getForceX(const float x)
{
	float over = 0;
	if (x > boundary.getMaxX()) {
		over = x - static_cast<float>(boundary.getMaxX());
	}
	else if (x < boundary.getMinX()) {
		over = x - static_cast<float>(boundary.getMinX());
	}

	const float force = getForce(over);
	return Vector3df(1, 0, 0) * force;
}

Vector3df SPHFlameBoundarySolver::getForceY(const float y)
{
	float over = 0;
	if (y > boundary.getMaxY()) {
		over = y - static_cast<float>(boundary.getMaxY());
	}
	else if (y < boundary.getMinY()) {
		over = y - static_cast<float>(boundary.getMinY());
	}
	const float force = getForce(over);
	return Vector3df(0, 1, 0) * force;
}

Vector3df SPHFlameBoundarySolver::getForceZ(const float z)
{
	float over = 0;
	if (z > boundary.getMaxZ()) {
		over = z - static_cast<float>(boundary.getMaxZ());
	}
	else if (z < boundary.getMinZ()) {
		over = z - static_cast<float>(boundary.getMinZ());
	}
	const float force = getForce(over);
	return Vector3df(0, 0, 1) * force;
}

float SPHFlameBoundarySolver::getForce(const float over)
{
	return -over / timeStep / timeStep;
}