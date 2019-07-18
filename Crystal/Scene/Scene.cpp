#include "Scene.h"

#include "SceneViewModel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
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
	Box3d bb;
	for (auto c : children) {
		c->getBoundingBox(bb);
	}

	return bb;
}

SceneViewModel Scene::toViewModel() const
{
	SceneViewModel viewModel;
	for (auto c : children) {
		auto& vm = c->toViewModel();
		viewModel.merge(vm);
	}
	return viewModel;
}

void Scene::addViewModel(SceneIdViewModel& viewModel) const
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}



