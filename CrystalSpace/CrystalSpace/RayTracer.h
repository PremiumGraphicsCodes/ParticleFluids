#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace Space {

class RayTracer
{
public:
	void buildSpace(const Shape::PolygonMesh& polygon, const double res);
};

	}
}