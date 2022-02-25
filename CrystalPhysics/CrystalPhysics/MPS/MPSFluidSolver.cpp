#include "MPSFluidSolver.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

#include <vector>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

namespace {
	constexpr int DIM = 3;
}

void MPSFluidSolver::step()
{
	std::vector<MPSParticle*> particles;
	CompactSpaceHash3d spaceHash(1.0, particles.size());

	/*
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}
	*/
}

Vector3df MPSFluidSolver::calculatePressureGradient(const MPSParticle* lhs, const MPSParticle* rhs, const float maxRadius)
{
	const float coe = DIM / lhs->getRestDensity();
	const float distanceSquared = Math::getDistanceSquared(lhs->getPositionf(), rhs->getPositionf());
	const auto vector = lhs->getPositionf() - rhs->getPositionf();
	const float pressureDiff = lhs->getPressure() - rhs->getPressure();
	const float weight = calculateWeight(std::sqrt(distanceSquared), maxRadius);
	return coe * pressureDiff / distanceSquared * vector * weight;
}

Vector3df MPSFluidSolver::calculateViscosity(const MPSParticle* lhs, const MPSParticle* rhs, const float maxRadius)
{
	const float coe = 2.0f * DIM / (lhs->getRestDensity() * lhs->getLamda0());
	const float distance = Math::getDistance(lhs->getPositionf(), rhs->getPositionf());
	const auto velocityDiff = rhs->getVelocity() - lhs->getVelocity();
	const float weight = calculateWeight(distance, maxRadius);
	return coe * velocityDiff * weight;
}

float MPSFluidSolver::calculateWeight(const float r, const float maxRadius)
{
	if (r > maxRadius) {
		return 0.0f;
	}
	return (r / maxRadius) - 1.0f;
}
