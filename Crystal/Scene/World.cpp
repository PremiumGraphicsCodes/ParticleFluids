#include "World.h"

#include "PointRenderer.h"
#include "LightScene.h"
#include "MaterialScene.h"
#include "TextureScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

World::World()
{
	scenes[0] = std::make_unique<Scene>(0, "Item");
	scenes[1] = std::make_unique<Scene>(0, "Root");
}

World::~World()
{
	clear();
}

void World::init()
{
	PointLight light;
	light.setPosition(Vector3dd(100, 100, 100));
	light.setAmbient(ColorRGBAf(1, 1, 1, 1));
	light.setDiffuse(ColorRGBAf(1, 1, 1, 1));
	light.setSpecular(ColorRGBAf(1, 1, 1, 1));
	scenes[1]->addScene(sceneFactory.createLightScene(light, "Light0"));

	{
		Material material;
		material.ambient = ColorRGBAf(1, 1, 1, 1);
		material.diffuse = ColorRGBAf(1, 1, 1, 1);
		material.specular = ColorRGBAf(1, 1, 1, 1);
		material.shininess = 1.0;
		scenes[1]->addScene(sceneFactory.createMaterialScene(material, "White"));
	}

	{
		Material material;
		material.ambient = ColorRGBAf(1, 0, 0, 1);
		material.diffuse = ColorRGBAf(0, 0, 0, 1);
		material.specular = ColorRGBAf(0, 0, 0, 1);
		material.shininess = 1.0;
		scenes[1]->addScene(sceneFactory.createMaterialScene(material, "Red"));
	}


	{
		Material material;
		material.ambient = ColorRGBAf(0, 0, 0, 1);
		material.diffuse = ColorRGBAf(0, 0, 0, 1);
		material.specular = ColorRGBAf(0, 0, 0, 1);
		material.shininess = 1.0;
		scenes[1]->addScene(sceneFactory.createMaterialScene(material, "Black"));
	}

	{
		Image image(1,1);
		image.setColor(0, 0, ColorRGBAuc(255, 255, 255, 255));
		scenes[1]->addScene(sceneFactory.createTextureScene(image, 3, "WhiteMat"));
	}

	{
		Image image(1, 1);
		image.setColor(0, 0, ColorRGBAuc(0, 0, 0, 0));
		scenes[1]->addScene(sceneFactory.createTextureScene(image, 4, "BlackMat"));
	}


	renderer = std::make_unique<UI::Renderer>();

}

void World::clear()
{
	sceneFactory.clear();
	for (auto& s : scenes) {
		s->clear();
	}
}

void World::clear(int layer)
{
	scenes[layer]->clear();
}

void World::addScene(int layer, IScene* scene)
{
	scenes[layer]->addScene(scene);
}

void World::updateViewModel()
{
	ViewModel vm;
	for (auto& s : scenes) {
		s->toViewModel(vm.object);
		s->toIdViewModel(vm.parentId, vm.childId);
	}

	this->viewModel = vm;
}

Box3d World::getBoundingBox() const
{
	return scenes[1]->getBoundingBox();
}
