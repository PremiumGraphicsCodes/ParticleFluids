#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "LinearOctree.h"

namespace Crystal {
	namespace Space {

class RayTracer : private UnCopyable
{
public:
	void buildSpace(const Shape::PolygonMesh& polygon, const Math::Box3dd& space, const int level);

	std::list<LinearOctreeCell*> trace(const Math::Ray3d& ray);

private:
	LinearOctreeOperator octree;
};

	}
}