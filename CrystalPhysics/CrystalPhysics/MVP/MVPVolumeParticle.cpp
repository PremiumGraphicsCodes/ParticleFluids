#include "MVPVolumeParticle.h"

#include "MVPFluidScene.h"

#include "../SPHKernel.h"

#include "../../../Crystal/Math/Gaussian1d.h"

#include "MVPParticleBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPVolumeParticle::MVPVolumeParticle(const float radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	restMass(0.0f)
{}

MVPVolumeParticle::~MVPVolumeParticle()
{
	for (auto p : massParticles) {
		delete p;
	}
	//points.clear();
}

void MVPVolumeParticle::setPressureCoe(const float c)
{
	this->pressureCoe = c;
	for (auto p : massParticles) {
		p->setPressureCoe(c);
	}
}

void MVPVolumeParticle::setViscosityCoe(const float c)
{
	for (auto p : massParticles) {
		p->setViscosityCoe(c);
	}
}

void MVPVolumeParticle::reset(bool resetMicro)
{
	this->force = Math::Vector3dd(0, 0, 0);
	if (resetMicro) {
		this->neighbors.clear();
		this->neighbors.reserve(64);
	}
}

void MVPVolumeParticle::calculateDensity()
{
	float mass = 0.0f;
	for (auto m : innerPoints) {
		mass += m->getMass();
	}
	this->density = (mass / restMass);
	/*
	for (auto m : innerPoints) {
		const auto p = (this->density - 1.0) * this->pressureCoe;
		m->setPressureCoe(p);
	}
	*/
}

void MVPVolumeParticle::calculatePressureForce(const float relaxationCoe)
{
	Math::Vector3df f(0, 0, 0);
	for (auto mp : innerPoints) {
		f += (this->position - mp->position) * mp->getMass() * mp->getPressureCoe();
	}
	this->force += f;
}

void MVPVolumeParticle::calculateViscosityForce()
{
	Math::Vector3df f(0, 0, 0);
	for (auto mp : innerPoints) {
		f -= ( this->velocity - mp->getVelocity()) * mp->getMass() * mp->getViscosityCoe();
	}
	this->force += f;
}

void MVPVolumeParticle::calculateVorticity()
{
	vorticity = Vector3df(0, 0, 0);
	for (auto mp : innerPoints) {
		const auto p = (mp->position - this->position);
		const auto v = (mp->getVelocity() - this->velocity);
		vorticity += glm::cross(p, v);
	}
}

void MVPVolumeParticle::stepTime(const float dt)
{
	const auto acc = (force) / getDensity();
	this->velocity += acc * dt;
	this->position += this->velocity * dt;
}

float MVPVolumeParticle::getDensity() const
{
	return this->density;
}

void MVPVolumeParticle::updateMicros()
{
	for (auto mp : this->massParticles) {
		mp->updatePosition();
	}
}

void MVPVolumeParticle::updateInnerPoints()
{
	const auto r = this->radius;
	innerPoints.clear();
	innerPoints = this->massParticles;
	for (auto n : this->neighbors) {
		for (auto mp : n->massParticles) {
			const auto distanceSquared = Math::getDistanceSquared(mp->position, this->position);
			if (distanceSquared < r * r) {
				innerPoints.push_back(mp);
			}
		}
	}
}
