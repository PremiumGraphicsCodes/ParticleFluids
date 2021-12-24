#include "DynamicOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

void DynamicOctree::divide(const float cellLength)
{
	if (this->particles.empty()) {
		return;
	}
	if (this->bb.getLength().x < cellLength * 4.0) {
		return;
	}

	std::vector<DynamicOctree> children;
	for (auto u = 0.0; u < 1.0; u += 0.5) {
		for (auto v = 0.0; v < 1.0; v += 0.5) {
			for (auto w = 0.0; w < 1.0; w += 0.5) {
				const auto v1 = bb.getPosition(u, v, w);
				const auto v2 = bb.getPosition(u + 0.5, v + 0.5, w + 0.5);
				const Box3dd subSpace(v1, v2);
				children.push_back(DynamicOctree(subSpace));
			}
		}
	}
	for (auto p : particles) {
		for (auto& c : children) {
			if (c.bb.contains(p->getPosition(), 1.0e-12)) {
				c.particles.push_back(p);
			}
		}
	}
	for (auto& c : children) {
		c.divide(cellLength);
	}
}
