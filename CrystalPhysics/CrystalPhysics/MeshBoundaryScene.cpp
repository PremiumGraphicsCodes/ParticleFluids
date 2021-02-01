#include "MeshBoundaryScene.h"

#include "MeshBoundaryScenePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

MeshBoundaryScene::MeshBoundaryScene(const int id, const std::string& name) :
	IScene(id, name),
	mesh(nullptr)
{
	this->controller = std::make_unique<MeshBoundaryScenePresenter>(this);
}


MeshBoundaryScene::~MeshBoundaryScene()
{
}

IPresenter* MeshBoundaryScene::getPresenter()
{
	return controller.get();
}

Box3d MeshBoundaryScene::getBoundingBox() const
{
	return mesh->getBoundingBox();
}