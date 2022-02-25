#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Shape/IParticle.h"
#include <list>

namespace Crystal {
	namespace Physics {

class MPSParticle : public Shape::IParticle
{
public:
	MPSParticle(const Math::Vector3df& position, const float radius) :
		position(position),
		radius(radius),
		acc(0.0)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	float getPressure() const { return pressure; }

	float getRestDensity() const { return n0; }

	float getLamda0() const { return lamda0; }

	void forwardTime(const float timeStep);

	void addNeighbor(MPSParticle* neighbor) { this->neighbors.push_back(neighbor); }

	void addExternalForce(const Math::Vector3df& externalForce) { this->force += externalForce; }

	void calculateViscosity(const float maxRadius);

private:
	Math::Vector3df calculatePressureGradient(const MPSParticle* rhs, const float maxRadius);

	Math::Vector3df calculateViscosity(const MPSParticle* rhs, const float maxRadius);

	float calculateWeight(const float r, const float maxRadius);

private:
	float pressure;
	float n0;
	float lamda0;
	const float radius;
	Math::Vector3df force;
	Math::Vector3df acc;
	Math::Vector3df position;
	Math::Vector3df velocity;
	std::list<MPSParticle*> neighbors;
};

	}
}