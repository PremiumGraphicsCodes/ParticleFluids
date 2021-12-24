#pragma once

#include <vector>

#include "Crystal/Math/Box3d.h"
#include "Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Space {

class DynamicOctree
{
public:
	explicit DynamicOctree(const Math::Box3dd& bb) :
		bb(bb)
	{}

	void divide(const float cellLength);

private:
	Math::Box3dd bb;
	std::vector<Shape::IParticle*> particles;
};

	}
}