#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "LinearOctree.h"

namespace Crystal {
	namespace Space {

class RayTraceItem : public LinearOctreeItem
{
public:
	explicit RayTraceItem(const Math::Triangle3d& triangle) :
		LinearOctreeItem(triangle.getBoundingBox())
	{}

	Math::Triangle3d getTriangle() const { return triangle; }

private:
	Math::Triangle3d triangle;
};

class RayTracer : private UnCopyable
{
public:
	void build(const Math::Box3dd& space, const int level);

	void add(RayTraceItem* item);

	std::list<const LinearOctreeCell*> trace(const Math::Ray3d& ray, const double pitch);

	void findCollisions(const std::list<const LinearOctreeCell*>& cells);

	//std::list<const LinearOctreeCell*> traceLv0(const Math::Ray3d& ray, const double pitch);

private:
	LinearOctree octree;
	std::vector<Math::Vector3dd> collisions;
};

	}
}