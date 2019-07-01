#include "Scene.h"

#include "SceneViewModel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::onClear()
{
	factory.clear();
}

Box3d Scene::getBoundingBox() const
{
	Box3d bb;
	for (auto c : children) {
		c->getBoundingBox(bb);
	}

	return bb;
}

void Scene::addViewModel(Crystal::UI::SceneViewModel& viewModel)
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}

void Scene::addViewModel(Crystal::UI::SceneIdViewModel& viewModel)
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}



