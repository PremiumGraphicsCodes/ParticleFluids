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
	void buildSpace(const Math::Box3dd& space, const int level);

	void add(LinearOctreeItem* item);

	std::list<const LinearOctreeCell*> trace(const Math::Ray3d& ray, const double pitch);

	//std::list<const LinearOctreeCell*> traceLv0(const Math::Ray3d& ray, const double pitch);


private:
	LinearOctree octree;
};

	}
}