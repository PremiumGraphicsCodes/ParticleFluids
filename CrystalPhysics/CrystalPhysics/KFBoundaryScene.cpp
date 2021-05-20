#include "KFBoundaryScene.h"

#include "KFBoundaryParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFBoundaryScene::KFBoundaryScene(const int id, const std::string& name) :
	IParticleSystemScene(id, name),
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
	//this->controller = std::make_unique<KFFluidScenePresenter>(this);
}

KFBoundaryScene::~KFBoundaryScene()
{
}

Box3dd KFBoundaryScene::getBoundingBox() const
{
	if (particles.empty()) {
		return Box3dd::createDegeneratedBox();
	}
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}

std::vector<Vector3dd> KFBoundaryScene::getPositions() const
{
	std::vector<Vector3dd> positions;
	for (auto p : particles) {
		positions.push_back(p->getPosition());
	}
	return positions;
}