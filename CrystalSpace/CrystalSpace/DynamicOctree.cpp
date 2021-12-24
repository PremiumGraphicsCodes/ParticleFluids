#include "DynamicOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void DynamicOctree::divide(const float cellLength, const std::vector<IParticle*>& particles)
{
	std::vector<IParticle*> inParticles;
	for (auto p : particles) {
		if (bb.contains(p->getPosition(), cellLength)) {
			inParticles.push_back(p);
		}
	}

	if (inParticles.empty()) {
		return;
	}
	if (this->bb.getLength().x < cellLength * 4.0) {
		this->particles = inParticles;
		return;
	}

	std::vector<DynamicOctree> children;
	for (auto u = 0.0; u < 1.0; u += 0.5) {
		for (auto v = 0.0; v < 1.0; v += 0.5) {
			for (auto w = 0.0; w < 1.0; w += 0.5) {
				const auto v1 = bb.getPosition(u, v, w);
				const auto v2 = bb.getPosition(u + 0.5, v + 0.5, w + 0.5);
				const Box3dd subSpace(v1, v2);
				DynamicOctree child(subSpace);
				child.divide(cellLength, inParticles);
			}
		}
	}
	for (auto& c : children) {
		c.divide(cellLength, inParticles);
	}
}
