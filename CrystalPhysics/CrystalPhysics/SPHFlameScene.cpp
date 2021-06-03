#include "SPHFlameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

SPHFlameScene::SPHFlameScene(const int id, const std::string& name) :
	Scene::IScene(id, name)
{
	//controller = std::make_unique<CSPHFluidSceneController>(this);
}

void SPHFlameScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3dd SPHFlameScene::getBoundingBox() const
{
	Box3dd bb = Box3dd::createDegeneratedBox();
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}