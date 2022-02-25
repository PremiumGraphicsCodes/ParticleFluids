#pragma once

#include "MPSParticle.h"

namespace Crystal {
	namespace Physics {


class MPSFluidSolver
{
public:
	void step();

	Math::Vector3df calculatePressureGradient(const MPSParticle* lhs, const MPSParticle* rhs, const float maxRadius);

	Math::Vector3df calculateViscosity(const MPSParticle* lhs, const MPSParticle* rhs, const float maxRadius);

	float calculateWeight(const float r, const float maxRadius);

private:
};
	}
}