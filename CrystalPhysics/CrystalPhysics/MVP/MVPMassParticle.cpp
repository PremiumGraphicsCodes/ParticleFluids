#include "MVPMassParticle.h"

#include "MVPVolumeParticle.h"
#include "MVPFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPMassParticle::MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass) :
	parent(parent),
	vector(point),
	mass(mass)
//	pressureCoe(parent->getScene()->getPressureCoe()),
//	viscosityCoe(parent->getScene()->getViscosityCoe())
{
	updatePosition(parent->getPositionf());
	updateVelocity(parent->getVelocity());
}


Vector3dd MVPMassParticle::getPosition() const
{
	return position;
}

Vector3df MVPMassParticle::getVelocity() const
{
	return velocity;
}

void MVPMassParticle::updatePosition(const Vector3df& parentPosition)
{
	//const auto v = (parent->getPositionf() - this->position);
	this->position = parentPosition + parent->getRadius() * vector;

	//const auto vv = glm::cross(vector, parent->getVorticity()) * 0.00f;
	//this->position += vv;

	//this->vector += vv;
	//this->vector = glm::normalize(this->vector);

}

void MVPMassParticle::updateVelocity(const Vector3df& parentVelocity)
{
	const auto vv = glm::cross(parent->getVorticity(), vector);
	this->velocity = parentVelocity + vv;
}

void MVPMassParticle::updateVector(const float dt)
{
	const auto l = Math::getLength(vector);
	const auto vv = glm::cross(parent->getVorticity(), vector) * dt;
	this->vector += vv;
	this->vector = glm::normalize(this->vector) * l;
}
