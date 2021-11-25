#pragma once

#include <vector>
#include "Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Physics {

class MVPSurfaceBuilder
{
public:
	void build(const std::vector<Math::Vector3df>& positions, const float searchRadius);

private:

};
	}
}