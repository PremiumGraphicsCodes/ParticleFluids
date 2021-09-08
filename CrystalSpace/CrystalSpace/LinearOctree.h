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

	std::list<IOctreeItem*> getItems() const { return items; }

private:
	//Math::Box3dd space;
	std::list<IOctreeItem*> items;
};

class LinearOctreeIndex
{
public:
	explicit LinearOctreeIndex(const unsigned int index1d) :
		index1d(index1d)
	{}

	std::pair<unsigned int, unsigned int> getLevelAndNumber() const;

	//unsigned int getNumber() const;

	unsigned int getIndex1d() const;

private:
	unsigned int index1d;
};

class LinearOctreeOperator : private UnCopyable
{
public:
	void init(const Math::Box3dd& space, const int level);

	void add(IOctreeItem* item);

	std::list<IOctreeItem*> findItems(const Math::Box3dd& space);

	unsigned int getParentLevel(const Math::Box3dd& space) const;

	Math::Box3dd calculateAABB(const LinearOctreeIndex& index) const;

	Math::Box3dd calculateAABBFromIndices(const std::array<unsigned int, 3>& indices) const;

	const std::vector<std::unique_ptr<LinearOctree>>& getTable() const { return tree; }

	Math::Vector3dd getMinBoxSize() const;

	std::array<unsigned int, 3> calculateGridIndex(const Math::Vector3dd& pos) const;

	//static unsigned int toIndex(const unsigned int level, const unsigned int number);

	//static std::pair<unsigned int, unsigned int> to

private:
	LinearOctree* root;
	Math::Box3dd rootSpace;
	std::vector<std::unique_ptr<LinearOctree>> tree;
	int maxLevel;
	double minWidth;

};

	}
}