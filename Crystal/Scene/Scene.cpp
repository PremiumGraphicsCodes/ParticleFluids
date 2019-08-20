#include "Scene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

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

void Scene::toViewModel(SceneViewModel& viewModel) const
{
	for (auto c : children) {
		c->toViewModel(viewModel);
	}
}

SceneIdViewModel Scene::toIdViewModel() const
{
	SceneIdViewModel viewModel;
	for (auto c : children) {
		auto& vm = c->toIdViewModel();
		viewModel.merge(vm);
	}
	return viewModel;
}



