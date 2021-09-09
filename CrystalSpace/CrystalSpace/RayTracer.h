#pragma once

#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "LinearOctree.h"

namespace Crystal {
	namespace Space {

class RayTracer
{
public:
	void buildSpace(const Shape::PolygonMesh& polygon, const double res);

	std::list<LinearOctree*> trace(const Math::Ray3d& ray);

private:
	LinearOctreeOperator octree;
};

	}
}