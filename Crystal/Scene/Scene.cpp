#include "Scene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

Scene::Scene(const int id, const std::string& name) :
	IScene(id, name)
{
}


Scene::~Scene()
{
}

void Scene::onClear()
{
}

Box3d Scene::getBoundingBox() const
{
	Box3d bb = Box3d::createDegeneratedBox();
	for (auto c : children) {
		if (bb.isDegenerated(1.0e-12)) {
			bb = c->getBoundingBox();
			continue;
		}
		auto b = c->getBoundingBox();
		if (b.isDegenerated(1.0e-12)) {
			continue;
		}
		bb.add(b);
	}
	if (bb.isDegenerated(1.0e-12)) {
		return Box3d();
	}

	return bb;
}

void Scene::send(SceneViewModel& viewModel) const
{
	for (auto c : children) {
		c->send(viewModel);
	}
}

void Scene::send(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const
{
	for (auto c : children) {
		c->send(parentIdViewModel, childIdViewModel);
	}
}



