#include "MicroParticle.h"

#include "KFMacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Vector3dd MicroParticle::getPosition() const
{
	return position;
}

Vector3df MicroParticle::getVelocity() const
{
	return parent->getVelocity();
}

void MicroParticle::updatePosition()
{
	this->position = parent->getPositionf() + parent->getRadius() * vector;
}
