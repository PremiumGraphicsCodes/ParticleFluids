#include "MPSFluidSolver.h"

using namespace Crystal::Physics;

namespace {
	constexpr int DIM = 3;
}

double MPSFluidSolver::calculatePressureGradient(const MPSParticle* lhs, const MPSParticle* rhs)
{
	const auto coe = DIM / lhs->getRestDensity();
	const auto distanceSquared = Math::getDistanceSquared(lhs->getPosition() - rhs->getPosition());
	const auto vector = lhs->getPosition() - rhs->getPosition();
	const auto pressureDiff = lhs->getPressure() - rhs->getPressure();
	return 0.0;
}

double MPSFluidSolver::calculateWeight(const double r, const double maxRadius)
{
	if (r > maxRadius) {
		return 0.0;
	}
	return (r / maxRadius) - 1.0;
}
