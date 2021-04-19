#pragma once

#include "../../Crystal/Shape/IParticle.h"
#include "SPHKernel.h"

namespace Crystal {
	namespace Physics {

class SPHSurfaceParticle : public Shape::IParticle
{
public:
	explicit SPHSurfaceParticle(const Math::Vector3dd& p) :
		position(p),
		weightedMean(),
		matrix(Math::identitiyMatrix()),
		density(0.0f)
	{}

	Math::Vector3dd getPosition() const { return position; }

	void correctedPosition(const float lamda);

	void calculateAnisotoropicMatrix(const std::vector<Shape::IParticle*>& neighbors, const float searchRadius);

	void calculateDensity(const std::vector<Shape::IParticle*>& neighbors, const float searchRadius, const SPHKernel& kernel);

	Math::Matrix3dd getMatrix() const { return matrix; }

	float getDensity() const { return density; }

private:
	Math::Vector3df position;
	Math::Vector3df weightedMean;

	Math::Matrix3dd matrix;
	float density;
};

	}
}