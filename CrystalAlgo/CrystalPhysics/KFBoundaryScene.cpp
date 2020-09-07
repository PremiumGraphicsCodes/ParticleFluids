#include "KFBoundaryScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFBoundaryScene::KFBoundaryScene(const int id, const std::string& name) :
	IScene(id, name),
	pressureCoe(10000.0),
	viscosityCoe(50.0)
{
	//this->controller = std::make_unique<KFFluidScenePresenter>(this);
}

KFBoundaryScene::~KFBoundaryScene()
{
	clearParticles();
}

void KFBoundaryScene::clearParticles()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

Box3d KFBoundaryScene::getBoundingBox() const
{
	Box3d bb(particles.front()->getPosition());
	for (auto p : particles) {
		bb.add(p->getPosition());
	}
	return bb;
}