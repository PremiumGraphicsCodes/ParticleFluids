#pragma once

#include <array>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Util/UnCopyable.h"

namespace Crystal {
	namespace Space {

class IOctreeItem
{
public:
	virtual ~IOctreeItem() {};

	virtual Math::Box3dd getBoundingBox() = 0;
};

class Octree //: private UnCopyable
{
public:
	Octree() {};

	explicit Octree(const Math::Box3dd& space);

	void add(IOctreeItem* item);

	void createChildren() const;

	bool isEmpty() const;

	std::vector<IOctreeItem*> getItems() const { return items; }

private:
	std::vector<IOctreeItem*> items;
	std::vector<Octree*> children;
	Math::Box3dd space;
};

	}
}