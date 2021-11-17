#pragma once

#include "../../../Crystal/Shape/IParticle.h"
#include "../SPHKernel.h"
#include <vector>

namespace Crystal {
	namespace Physics {

class SPHSurfaceParticle : public Shape::IParticle
{
public:
	explicit SPHSurfaceParticle(const Math::Vector3dd& p, const float mass) :
		position(p),
		matrix(Math::identitiyMatrix<double>()),
		density(0.0f),
		mass(mass)
	{}

	Math::Vector3dd getPosition() const { return position; }

	void correctedPosition(const float lamda, const Math::Vector3df& weightedMean);

	void calculateAnisotoropicMatrix(const std::vector<Shape::IParticle*>& neighbors, const float searchRadius);

	void calculateDensity(const std::vector<Shape::IParticle*>& neighbors, const float searchRadius, const SPHKernel& kernel);

	Math::Matrix3dd getMatrix() const { return matrix; }

	float getDensity() const { return density; }

	float getMass() const { return mass; }

private:
	Math::Vector3df position;
	Math::Matrix3dd matrix;
	float density;
	float mass;
};

	}
}