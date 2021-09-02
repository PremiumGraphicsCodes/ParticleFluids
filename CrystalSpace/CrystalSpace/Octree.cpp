#include "Octree.h"
#include "Overlap.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

Octree::Octree(const Box3dd& space) :
	space(space)
{}

void Octree::add(IOctreeItem* item)
{
	if (Overlap::overlap(this->space, item->getTriangle())) {
		this->items.push_back(item);
		if (children.empty()) {
			createChildren();
		}
		for (auto c : children) {
			c->add(item);
		}
	}
}

void Octree::createChildren()
{
	for (auto u = 0.0; u < 1.0; ++u) {
		for (auto v = 0.0; v < 1.0; ++v) {
			for (auto w = 0.0; w < 1.0; ++w) {
				const auto v1 = space.getPosition(u, v, w);
				const auto v2 = space.getPosition(u + 0.5, v + 0.5, w + 0.5);
				const Box3dd subSpace(v1, v2);
				children.push_back(new Octree(subSpace));
			}
		}
	}
}

bool Octree::isEmpty() const
{
	return items.empty();
}
