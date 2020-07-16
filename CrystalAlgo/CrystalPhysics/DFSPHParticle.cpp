#include "DFSPHParticle.h"
#include "SPHConstant.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

double DFSPHParticle::getMass() const
{
	const auto diameter = radius * 2.0;
	return constant->getDensity() * diameter * diameter * diameter;
}

void DFSPHParticle::calculateDensity()
{
	this->density = 0.0;
	this->density += (kernel->getCubicSpline(0.0, kernel->getEffectLength()) * this->getMass());
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
		const auto v = this->getPosition() - n->position;
		const auto weight = (kernel->getCubicSplineGradient(v, kernel->getEffectLength()) * (float)n->getMass());
		a += weight;
		b += Math::getLengthSquared(weight);
	}

	this->alpha += Math::getLengthSquared(a) + b;
}

double DFSPHParticle::calculateDpDt()
{
	this->dpdt = 0.0;
	for (auto n : neighbors) {
		const auto v = this->position - n->getPosition();
		//const auto grad = kernel->getCubicSplineGradient(velocity, kernel->getEffectLength());
		//dpdt += Math::getLengthSquared(glm::dot(this->velocity, grad));
	}
	this->dpdt *= -density;
}

void DFSPHParticle::calculateVelocityInDivergenceError()
{

}
