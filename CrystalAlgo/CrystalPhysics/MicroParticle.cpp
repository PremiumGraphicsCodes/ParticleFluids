#include "MicroParticle.h"

#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Vector3dd MicroParticle::getPosition() const
{
	return parent->getPosition() + parent->getRadius() * vector;
}

Vector3dd MicroParticle::getVelocity() const
{
	return parent->getVelocity();
}
