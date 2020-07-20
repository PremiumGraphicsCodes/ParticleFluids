#include "PBSPHParticle.h"

#include "SPHKernel.h"

#include "PBFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


PBSPHParticle::PBSPHParticle(const Vector3df& center, const float radius, PBFluidScene* scene) :
	position(center),
	radius(radius),
//	ISPHParticle(center, radius),
	scene(scene)
{
	this->density = scene->getConstant()->getDensity();
}

void PBSPHParticle::init()
{
	density = 0.0;
	dx = Math::Vector3df(0.0f, 0.0f, 0.0f);
	normal = Math::Vector3df(0.0f, 0.0f, 0.0f);
	force = Math::Vector3df(0.0f, 0.0f, 0.0f);
	this->predictPosition = this->position;
}

float PBSPHParticle::getDensityRatio() const
{
	return density / scene->getConstant()->getDensity();
}

float PBSPHParticle::getMass() const
{
	const auto diameter = radius * 2.0;
	return scene->getConstant()->getDensity() * diameter * diameter * diameter;
}

float PBSPHParticle::getVolume() const
{
	return getMass() / density;
}

float PBSPHParticle::getRestVolume() const
{
	return getMass() / scene->getConstant()->getDensity();
}

void PBSPHParticle::setDefaultDensity()
{
	this->density = scene->getConstant()->getDensity();
}

void PBSPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc * timeStep);
	this->position += (this->velocity * timeStep);
}

void PBSPHParticle::addExternalForce(const Vector3df& externalForce)
{
	this->force += externalForce * getMass();//constant->getDensity();
}

void PBSPHParticle::addSelfDensity()
{
	this->addDensity(getKernel()->getPoly6Kernel(0.0, getKernel()->getEffectLength()) * this->getMass());
}

void PBSPHParticle::addDensity(const PBSPHParticle& rhs)
{
	const float distance = glm::distance(this->getPredictPosition(), rhs.getPredictPosition());
	this->addDensity(scene->getKernel()->getPoly6Kernel(distance, getKernel()->getEffectLength()) * rhs.getMass());
}

void PBSPHParticle::addDensity(const float distance, const float mass)
{
	this->addDensity(getKernel()->getPoly6Kernel(distance, getKernel()->getEffectLength()) * mass);
}

void PBSPHParticle::predictPosition_(const float dt)
{
	this->position = this->predictPosition;
	this->velocity += dt * this->force;
	this->predictPosition += dt * this->velocity;
}

void PBSPHParticle::updatePredictPosition()
{
	this->predictPosition += dx;
}

void PBSPHParticle::updateVelocity(const float dt)
{
	this->velocity = (this->predictPosition - this->position) / dt;
}

void PBSPHParticle::updatePosition()
{
	this->position = this->predictPosition;
}

void PBSPHParticle::addPositionCorrection(const Vector3df& distanceVector)
{
	this->dx += distanceVector;
	//const auto pc = 1.0f / this->constant->getDensity() * (this->densityConstraint + this->densityConstraint) * kernel.getSpikyKernelGradient(distanceVector, constant->getEffectLength());
	//this->positionCorrection += pc;
}

Vector3df PBSPHParticle::getDiff(const PBSPHParticle& rhs) const
{
	//return this->getPosition() - rhs.getPosition();
	return rhs.getPosition() - this->getPosition();
}

float PBSPHParticle::getEffectLength() const
{
	return scene->getConstant()->getEffectLength();
}

void PBSPHParticle::calculatePressure(const PBSPHParticle& rhs)
{
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto weight = getKernel()->getPoly6KernelGradient(v, getKernel()->getEffectLength());
	const auto c = this->getConstraint() + rhs.getConstraint();
	dx += c * weight / this->getDensity() * 0.05f;
}

void PBSPHParticle::calculatePressure(const Vector3df& v)
{
	const auto weight = getKernel()->getPoly6KernelGradient(v, getKernel()->getEffectLength());
	const auto c = this->getConstraint() + this->getConstraint();
	dx += c * weight / this->getDensity() * 0.5f;
}

void PBSPHParticle::calculateViscosity(const PBSPHParticle& rhs)
{
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto vel = rhs.getVelocity() - this->velocity;
	const auto weight = getKernel()->getViscosityKernelLaplacian(glm::length(v), getKernel()->getEffectLength());
	this->xvisc += vel * weight * 0.1f;
}

float PBSPHParticle::getConstraint() const
{
	return std::max(getDensityRatio() - 1.0f, 0.0f);
}

SPHKernel* PBSPHParticle::getKernel()
{
	return scene->getKernel();
}
