#include "MVPMassParticle.h"

#include "MVPVolumeParticle.h"
#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPMassParticle::MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass) :
	parent(parent),
	vector(point),
	mass(mass)
//	pressureCoe(parent->getScene()->getPressureCoe()),
//	viscosityCoe(parent->getScene()->getViscosityCoe())
{
	updatePosition();
}


Vector3dd MVPMassParticle::getPosition() const
{
	return position;
}

Vector3df MVPMassParticle::getVelocity() const
{
	return parent->getVelocity();
}

void MVPMassParticle::updatePosition()
{
	this->position = parent->getPositionf() + parent->getRadius() * vector;
}
