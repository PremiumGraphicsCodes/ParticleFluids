#include "DynamicOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void DynamicOctree::divide(const float cellLength, const std::vector<IParticle*>& particles)
{
	if (this->bb.getLength().x < cellLength * 4.0) {
		this->particles = particles;
		return;
	}

	for (auto u = 0.0; u < 1.0; u += 0.5) {
		for (auto v = 0.0; v < 1.0; v += 0.5) {
			for (auto w = 0.0; w < 1.0; w += 0.5) {
				const auto v1 = bb.getPosition(u, v, w);
				const auto v2 = bb.getPosition(u + 0.5, v + 0.5, w + 0.5);
				const Box3dd subSpace(v1, v2);
				DynamicOctree* child = new DynamicOctree(subSpace);
				std::vector<IParticle*> inParticles;
				for (auto p : particles) {
					if (subSpace.contains(p->getPosition(), cellLength)) {
						inParticles.push_back(p);
					}
				}
				if (inParticles.empty()) {
					continue;
				}
				child->divide(cellLength, inParticles);
				this->children.push_back(child);
			}
		}
	}
}

std::list<DynamicOctree*> DynamicOctree::toSerialList()
{
	std::list<DynamicOctree*> results;
	results.push_back(this);
	for (auto c : children) {
		/*
		if (c->isEmpty()) {
			continue;
		}
		*/
		auto list = c->toSerialList();
		results.insert(results.end(), list.begin(), list.end());
	}
	return results;
}
