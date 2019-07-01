#include "Scene.h"

#include "SceneViewModel.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

Scene::Scene()
{
	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPosition(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	addScene( factory.createLightScene(light, "Light") );

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

void Scene::addViewModel(Crystal::UI::SceneViewModel& viewModel) const
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}

void Scene::addViewModel(Crystal::UI::SceneIdViewModel& viewModel) const
{
	for (auto c : children) {
		c->addViewModel(viewModel);
	}
}



