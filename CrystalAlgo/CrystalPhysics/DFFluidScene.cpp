#include "DFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Box3d DFFluidScene::getBoundingBox() const
{
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}