#include "MPSParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	constexpr int DIM = 3;
}

void MPSParticle::forwardTime(const float timeStep)
{
	//const auto& acc = getAccelaration() / getDensity();
	this->velocity += (acc * timeStep);
	this->position += (velocity * timeStep);
}

void MPSParticle::calculateViscosity(const float maxRadius)
{
	for (auto n : neighbors) {
		this->acc += this->calculateViscosity(n, maxRadius);
	}
}

Vector3df MPSParticle::calculatePressureGradient(const MPSParticle* rhs, const float maxRadius)
{
	const float coe = DIM / this->getRestDensity();
	const float distanceSquared = getDistanceSquared(this->getPositionf(), rhs->getPositionf());
	const auto vector = rhs->getPositionf() - this->getPositionf();
	const float pressureDiff = rhs->getPressure() - this->getPressure();
	const float weight = calculateWeight(std::sqrt(distanceSquared), maxRadius);
	return coe * pressureDiff / distanceSquared * vector * weight;
}

Vector3df MPSParticle::calculateViscosity(const MPSParticle* rhs, const float maxRadius)
{
	const float coe = 2.0f * DIM / (this->getRestDensity() * this->getLamda0());
	const float distance = getDistance(this->getPositionf(), rhs->getPositionf());
	const auto velocityDiff = rhs->getVelocity() - this->getVelocity();
	const float weight = calculateWeight(distance, maxRadius);
	return coe * velocityDiff * weight;
}

float MPSParticle::calculateWeight(const float r, const float maxRadius)
{
	if (r > maxRadius) {
		return 0.0f;
	}
	return (r / maxRadius) - 1.0f;
}
