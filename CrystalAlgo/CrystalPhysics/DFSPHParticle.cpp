#include "DFSPHParticle.h"
#include "SPHConstant.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float DFSPHParticle::getMass() const
{
	const auto diameter = radius * 2.0;
	return constant->getDensity() * diameter * diameter * diameter;
}

void DFSPHParticle::calculateDensity()
{
	this->density = 0.0;
	this->density += (kernel->getCubicSpline(0.0f, kernel->getEffectLength()) * this->getMass());
	for (auto n : neighbors) {
		const auto distance = glm::distance(this->getPosition(), n->getPosition());
		this->density += (kernel->getCubicSpline(distance, kernel->getEffectLength()) * n->getMass());
	}
}

void DFSPHParticle::calculateAlpha()
{
	this->alpha = 0.0;

	Vector3dd a(0,0,0);
	double b = 0.0;
	for (auto n : neighbors) {
		const auto v = this->position - n->position;
		const auto weight = (kernel->getCubicSplineGradient(v, kernel->getEffectLength()) * (float)n->getMass());
		a += weight;
		b += Math::getLengthSquared(weight);
	}

	this->alpha += Math::getLengthSquared(a) + b;
}

void DFSPHParticle::calculateDpDt()
{
	this->dpdt = 0.0;
	for (auto n : neighbors) {
		const auto v = this->position - n->position;
		const auto grad = kernel->getCubicSplineGradient(v, kernel->getEffectLength());
		dpdt += glm::dot(this->velocity, grad);
	}
	this->dpdt *= -density;
}

void DFSPHParticle::predictDensity(const double dt)
{
	calculateDpDt();
	predictedDensity = density + dt * dpdt;
}

void DFSPHParticle::calculateVelocityInDivergenceError(const float dt)
{
	const auto k_i = 1.0f / dt * dpdt * alpha;
	Vector3df dv(0,0,0);
	for (auto n : neighbors) {
		const auto k_j = 1.0f / dt * n->dpdt * n->alpha;
		const auto v = this->position - n->position;
		dv += n->getMass()* (k_i / density + k_j / n->density) * kernel->getCubicSplineGradient(v, kernel->getEffectLength());
	}
	this->velocity -= dt * dv;
}

void DFSPHParticle::calculateVelocityInDensityError(const float dt)
{
	const auto k_i = (this->predictedDensity - constant->getDensity()) / dt / dt * alpha;
	Vector3df dv(0, 0, 0);
	for (auto n : neighbors) {
		const auto k_j = (n->predictedDensity - constant->getDensity()) / dt / dt * n->alpha;
		const auto v = this->position - n->position;
		dv += n->getMass() * (k_i / density + k_j / n->density) * kernel->getCubicSplineGradient(v, kernel->getEffectLength());
	}
	this->velocity -= dt * dv;
}
