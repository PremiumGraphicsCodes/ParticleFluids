#pragma once

#include <vector>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Physics {

class SPHSmoothSurfaceConstructor
{
public:
	void add(Shape::IParticle* particle);

	void construct(const float searchRadius);

private:
	std::vector<Shape::IParticle*> particles;
};
	}
}