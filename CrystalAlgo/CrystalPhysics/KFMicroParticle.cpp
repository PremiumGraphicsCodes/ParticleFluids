#include "KFMicroParticle.h"

#include "KFMacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Vector3dd KFMicroParticle::getPosition() const
{
	return position;
}

Vector3df KFMicroParticle::getVelocity() const
{
	return parent->getVelocity();
}

void KFMicroParticle::updatePosition()
{
	this->position = parent->getPositionf() + parent->getRadius() * vector;
}
