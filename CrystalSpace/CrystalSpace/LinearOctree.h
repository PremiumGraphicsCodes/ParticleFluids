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

class LinearOctreeItem
{
public:
	explicit LinearOctreeItem(const Math::Box3dd& box) :
		box(box)
	{}
	
	Math::Box3dd getBoundingBox() const { return box; }

private:
	Math::Box3dd box;
};

class LinearOctree
{
public:
	LinearOctree(/*const Math::Box3dd& space*/)// :
		//space(space)
	{}

	//Math::Box3dd getSpace() const { return space; }

	void add(LinearOctreeItem* item) { this->items.push_back(item); }

	std::list<LinearOctreeItem*> getItems() const { return items; }

private:
	//Math::Box3dd space;
	std::list<LinearOctreeItem*> items;
};

class LinearOctreeIndex
{
public:
	explicit LinearOctreeIndex(const unsigned int index1d) :
		index1d(index1d)
	{}

	LinearOctreeIndex(const unsigned int level, const unsigned int number);

	std::pair<unsigned int, unsigned int> getLevelAndNumber() const;

	//unsigned int getNumber() const;

	unsigned int getIndex1d() const;

	bool operator==(const LinearOctreeIndex& rhs) const { return this->index1d == rhs.index1d; }

private:
	unsigned int index1d;
};

class LinearOctreeOperator : private UnCopyable
{
public:
	void init(const Math::Box3dd& space, const int level);

	void add(LinearOctreeItem* item);

	std::list<LinearOctreeItem*> findItems(const Math::Box3dd& space);

	LinearOctreeIndex getIndex(const Math::Box3dd& space) const;

	Math::Box3dd calculateAABB(const LinearOctreeIndex& index) const;

	Math::Box3dd calculateAABB(const std::array<unsigned int, 3>& indices) const;

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
	//double minWidth;

};

	}
}