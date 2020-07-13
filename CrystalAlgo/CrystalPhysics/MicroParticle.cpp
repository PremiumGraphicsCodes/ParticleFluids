#include "MicroParticle.h"

#include "KFMacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Vector3dd MicroParticle::getPosition() const
{
	return position;
}

Vector3dd MicroParticle::getVelocity() const
{
	return parent->getVelocity();
}

void MicroParticle::updatePosition()
{
	this->position = parent->getPosition() + parent->getRadius() * vector;
}
