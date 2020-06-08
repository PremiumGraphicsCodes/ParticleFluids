#include "MicroParticle.h"

#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Algo::Physics;

Vector3dd MicroParticle::getPosition() const
{
	return vector;
}

Vector3dd MicroParticle::getVelocity() const
{
	return parent->getVelocity();
}
