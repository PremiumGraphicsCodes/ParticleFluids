#pragma once

#include "Crystal/Math/Vector3d.h"

#include "Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class MPSParticle : public Shape::IParticle
{
public:
	Math::Vector3dd getPosition() const override { return position; }

	float getPressure() const { return pressure; }

	float getRestDensity() const { return n0; }

private:
	float pressure;
	float n0;
	Math::Vector3df position;
};

class MPSFluidSolver
{
public:

	double calculatePressureGradient(const MPSParticle* lhs, const MPSParticle* rhs);

	double calculateWeight(const double r, const double maxRadius);

private:
};
	}
}