#include "FluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

FluidScene::FluidScene(const int id, const std::string& name) :
	IScene(id, name)
{
	this->controller = std::make_unique<FluidSceneController>(this);
}

FluidScene::~FluidScene()
{
	clearParticles();
}

void FluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3d FluidScene::getBoundingBox() const
{
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}