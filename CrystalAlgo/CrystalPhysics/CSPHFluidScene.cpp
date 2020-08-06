#include "CSPHFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

CSPHFluidScene::CSPHFluidScene(const int id, const std::string& name) :
	Scene::IScene(id, name)
{
	//controller = std::make_unique<DFFluidSceneController>(this);
}

void CSPHFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3d CSPHFluidScene::getBoundingBox() const
{
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}