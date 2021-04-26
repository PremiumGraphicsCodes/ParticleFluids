#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

IKFFluidScene::IKFFluidScene(const int id, const std::string& name) :
	IParticleSystemScene(id, name),
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
	this->controller = std::make_unique<KFFluidScenePresenter>(this);
}

KFFluidScene::KFFluidScene(const int id, const std::string& name) :
	IKFFluidScene(id, name),
	isBoundary_(false)
{
}

IKFFluidScene::~IKFFluidScene()
{
	clearParticles();
}

void IKFFluidScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3d IKFFluidScene::getBoundingBox() const
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

std::vector<Vector3dd> IKFFluidScene::getPositions() const
{
	std::vector<Vector3dd> positions;
	for (auto p : particles) {
		positions.push_back(p->getPosition());
	}
	return positions;
}