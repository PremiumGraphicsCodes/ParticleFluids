#include "KFMicroParticle.h"

#include "KFMacroParticle.h"
#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

KFMicroParticle::KFMicroParticle(KFMacroParticle* parent, const Math::Vector3df& point, const float mass) :
	parent(parent),
	vector(point),
	mass(mass)
//	pressureCoe(parent->getScene()->getPressureCoe()),
//	viscosityCoe(parent->getScene()->getViscosityCoe())
{
	updatePosition();
}


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
