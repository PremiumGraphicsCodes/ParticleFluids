#pragma once

#include <vector>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Physics {

class SPHSurfaceBuilder
{
public:
	void add(Shape::IParticle* particle);

	void build(const float searchRadius);

private:
	std::vector<Shape::IParticle*> particles;
};
	}
}