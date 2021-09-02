#pragma once

#include <array>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Space {

class IOctreeItem
{
public:
	explicit IOctreeItem(const Math::Triangle3d& triangle) :
		triangle(triangle)
	{}

	virtual ~IOctreeItem() {};

	Math::Box3dd getBoundingBox() const { return triangle.getBoundingBox(); }

	Math::Triangle3d getTriangle() const { return triangle; }

private:
	Math::Triangle3d triangle;
};

class Octree : private UnCopyable
{
public:
	Octree() : level(0)
	{};

	Octree(const Math::Box3dd& space, const int level);

	void add(IOctreeItem* item);

	void createChildren();

	bool isEmpty() const;

	std::vector<IOctreeItem*> getItems() const { return items; }

private:
	std::vector<IOctreeItem*> items;
	std::vector<Octree*> children;
	Math::Box3dd space;
	const int level;
};

	}
}