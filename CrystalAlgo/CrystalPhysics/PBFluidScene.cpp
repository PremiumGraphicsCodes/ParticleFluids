#include "PBFluidScene.h"

#include "PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

PBFluidScene::PBFluidScene(const int id, const std::string& name) :
	IScene(id, name)
{
	this->controller = std::make_unique<PBFluidSceneController>(this);
}

void PBFluidScene::clearParticles()
{
	particles.clear();
}

Box3d PBFluidScene::getBoundingBox() const
{
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}