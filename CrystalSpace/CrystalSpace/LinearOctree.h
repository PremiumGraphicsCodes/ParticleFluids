#pragma once

#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Space {

class LinearOctree
{
public:
	explicit LinearOctree(const Math::Box3dd& space) :
		space(space)
	{}

	Math::Box3dd CalculateOctreeBoxAABBFromMortonNumber(const unsigned int number);

private:
	Math::Box3dd space;
};

	}
}