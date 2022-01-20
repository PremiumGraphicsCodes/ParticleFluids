#include "MVPMassParticle.h"

#include "MVPVolumeParticle.h"
#include "MVPFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPMassParticle::MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass) :
	parent(parent),
	mass(mass)
//	pressureCoe(parent->getScene()->getPressureCoe()),
//	viscosityCoe(parent->getScene()->getViscosityCoe())
{
	this->position = point;
	//updatePosition(parent->getPositionf());
	//updateVelocity(parent->getVelocity());
}

void MVPMassParticle::setParent(MVPVolumeParticle* p)
{
	this->parent = p;
	this->vector = this->position - p->getPositionf();
	//updatePosition(parent->getPositionf());
	//updateVelocity(parent->getVelocity());
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
	//this->position += v;
	this->position = parentPosition + parent->getRadius() * vector;
	assert(!::isnan(this->position.x));

	//const auto vv = glm::cross(vector, parent->getVorticity()) * 0.00f;
	//this->position += vv;

	//this->vector += vv;
	//this->vector = glm::normalize(this->vector);

}

void MVPMassParticle::updateVelocity(const Vector3df& parentVelocity)
{
	assert(!::isnan(this->velocity.x));
	this->velocity = parentVelocity;
	assert(!::isnan(this->velocity.x));
	/*
	if (Math::getLength(parent->getVorticity()) > 1.0e-3) {
		this->velocity += glm::cross(parent->getVorticity(), vector);
	}
	*/
}

/*
void MVPMassParticle::updateVector(const float dt)
{
	const auto l = Math::getLength(vector);
	const auto vv = glm::cross(parent->getVorticity(), vector) * dt;
	this->vector += vv;
	this->vector = glm::normalize(this->vector) * l;
}
*/
