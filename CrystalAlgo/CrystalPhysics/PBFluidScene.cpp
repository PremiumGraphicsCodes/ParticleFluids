#include "PBFluidScene.h"

#include "PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

PBFluidScene::PBFluidScene(const int id, const std::string& name, const SPHKernel& kernel) :
	IScene(id, name),
	kernel(kernel)
{
	this->controller = std::make_unique<PBFluidSceneController>(this);
}

PBFluidScene::~PBFluidScene()
{
	clearParticles();
}

void PBFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
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