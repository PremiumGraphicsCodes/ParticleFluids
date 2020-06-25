#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFFluidScene::KFFluidScene(const int id, const std::string& name) :
	IScene(id, name)
{
	this->controller = std::make_unique<FluidSceneController>(this);
}

KFFluidScene::~KFFluidScene()
{
	clearParticles();
}

void KFFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3d KFFluidScene::getBoundingBox() const
{
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}