#pragma once

#include <vector>

#include "../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class SPHSurfaceParticle : public Shape::IParticle
{
public:
	SPHSurfaceParticle(const Math::Vector3dd& p) :
		position(p)
	{}

	Math::Vector3dd getPosition() const { return position; }

	Math::Matrix3dd matrix;

private:
	Math::Vector3dd position;
};

class SPHSurfaceBuilder
{
public:
	//void add(Shape::IParticle* particle);

	void build(const std::vector<Math::Vector3dd>& positions, const float searchRadius);

private:
	//std::vector<Shape::IParticle*> particles;
};
	}
}