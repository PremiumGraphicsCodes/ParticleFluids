#pragma once

#include "IOctreeItem.h"

#include "../../Crystal/Math/Box3d.h"
#include <vector>
#include <list>

namespace Crystal {
	namespace Space {

class LinearOctree
{
public:
	LinearOctree(/*const Math::Box3dd& space*/)// :
		//space(space)
	{}

	//Math::Box3dd getSpace() const { return space; }


private:
	//Math::Box3dd space;
	std::list<IOctreeItem*> item;
};

class LinearOctreeOperator
{
public:
	void init(const Math::Box3dd& space, const int level);

	void add(IOctreeItem* item);

	Math::Box3dd calculateAABBFromMortonNumber(const unsigned int number);

	const std::vector<LinearOctree*>& getTable() const { return tree; }

private:
	LinearOctree* root;
	Math::Box3dd rootSpace;
	std::vector<LinearOctree*> tree;
	double minWidth;

};

	}
}