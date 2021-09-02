#include "Octree.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

Octree::Octree(const Box3dd& space) :
	space(space)
{}

void Octree::add(IOctreeItem* item)
{
	this->items.push_back(item);
}

void Octree::createChildren() const
{
}

bool Octree::isEmpty() const
{
	return items.empty();
}
