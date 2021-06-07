#include "SPHFlameParticle.h"

#include "../SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

SPHFlameParticle::SPHFlameParticle(const Vector3df& center, const float radius, SPHConstant* constant, SPHFlameConstant* flameConstant) :
	CSPHParticle(center, radius, constant),
	flameConstant(flameConstant),
	temperature(300.0f),
	fuel(0.0f)
{}

void SPHFlameParticle::solveHeatDiffuse(const SPHFlameParticle& rhs)
{
	const auto coe = (this->flameConstant->k_hd + rhs.flameConstant->k_hd) * 0.5f;
	const auto temperatureDiff = (rhs.temperature - this->temperature);
	const auto distance = Math::getDistance(getPosition(), rhs.getPosition());
	this->temperature += (coe * temperatureDiff * kernel->getViscosityKernelLaplacian(distance) * rhs.getVolume());
}

void SPHFlameParticle::solveFuelDiffuse(const SPHFlameParticle& rhs)
{
	const auto coe = (this->flameConstant->k_fd + rhs.flameConstant->k_fd) * 0.5f;
	const auto fuelDiff = (rhs.fuel - this->fuel);
	const auto distance = Math::getDistance(getPosition(), rhs.getPosition());
	this->fuel += (coe * fuelDiff * kernel->getViscosityKernelLaplacian(distance) * rhs.getVolume());
}

float SPHFlameParticle::getReactionSpeed()
{
	return flameConstant->k_rs * temperature * fuel;
}
