#pragma once

#include "IOctreeItem.h"

#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Util/UnCopyable.h"
#include <vector>
#include <list>
#include <memory>

namespace Crystal {
	namespace Space {

class LinearOctree
{
public:
	LinearOctree(/*const Math::Box3dd& space*/)// :
		//space(space)
	{}

	//Math::Box3dd getSpace() const { return space; }

	void add(IOctreeItem* item) { this->items.push_back(item); }


private:
	//Math::Box3dd space;
	std::list<IOctreeItem*> items;
};

class LinearOctreeOperator : private UnCopyable
{
public:
	void init(const Math::Box3dd& space, const int level);

	void add(IOctreeItem* item);

	Math::Box3dd calculateAABBFromMortonNumber(const unsigned int number);

	Math::Box3dd calculateAABBFromIndices(const std::array<unsigned int, 3>& indices) const;

	std::list<IOctreeItem*> findCollisions(const Math::Ray3d& ray);

	const std::vector<std::unique_ptr<LinearOctree>>& getTable() const { return tree; }

	Math::Vector3dd getMinBoxSize() const;

	std::array<unsigned int, 3> calculateGridIndex(const Math::Vector3dd& pos) const;

private:
	LinearOctree* root;
	Math::Box3dd rootSpace;
	std::vector<std::unique_ptr<LinearOctree>> tree;
	int maxLevel;
	double minWidth;

};

	}
}