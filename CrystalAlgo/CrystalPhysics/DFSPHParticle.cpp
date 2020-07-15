#include "DFSPHParticle.h"
#include "SPHConstant.h"

using namespace Crystal::Physics;

double DFSPHParticle::getMass() const
{
	const auto diameter = radius * 2.0;
	return constant->getDensity() * diameter * diameter * diameter;
}

void DFSPHParticle::addSelfDensity()
{
	this->density += (kernel->getPoly6Kernel(0.0, kernel->getEffectLength()) * this->getMass());
}

void DFSPHParticle::addDensity(const DFSPHParticle& rhs)
{
	const float distance = glm::distance(this->getPosition(), rhs.getPosition());
	this->density += (kernel->getPoly6Kernel(distance, kernel->getEffectLength()) * rhs.getMass());
}

void DFSPHParticle::addDensity(const float distance, const float mass)
{
	this->density += (kernel->getPoly6Kernel(distance, kernel->getEffectLength()) * mass);
}
