#include "SPHFlameParticle.h"

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
	/*
	const auto viscosityCoe = (this->constant->getViscosityCoe() + rhs.constant->getViscosityCoe()) * 0.5f;
	const auto& velocityDiff = (rhs.velocity - this->velocity);
	const auto distance = Math::getDistance(getPosition(), rhs.getPosition());
	this->addForce(viscosityCoe * velocityDiff * kernel->getViscosityKernelLaplacian(distance) * rhs.getVolume());
	*/
}

void SPHFlameParticle::solveFuelDiffuse(const SPHFlameParticle& rhs)
{

}

float SPHFlameParticle::getReactionSpeed()
{
	return flameConstant->k_rs * temperature * fuel;
}
