#include "KFFluidEmitterScene.h"

#include "KFMacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFFluidEmitterScene::KFFluidEmitterScene(const int id, const std::string& name) :
	IParticleSystemScene(id, name),
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
	//this->controller = std::make_unique<KFFluidScenePresenter>(this);
}

KFFluidEmitterScene::~KFFluidEmitterScene()
{
	clearParticles();
}

void KFFluidEmitterScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3d KFFluidEmitterScene::getBoundingBox() const
{
	if (particles.empty()) {
		return Box3d::createDegeneratedBox();
	}
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

std::vector<Vector3dd> KFFluidEmitterScene::getPositions() const
{
	std::vector<Vector3dd> positions;
	for (auto p : particles) {
		positions.push_back(p->getPosition());
	}
	return positions;
}