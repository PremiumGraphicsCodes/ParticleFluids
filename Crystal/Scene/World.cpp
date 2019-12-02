#include "World.h"

#include "PointRenderer.h"

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
	scenes[1]->addScene(objectFactory.createLightScene(light, "Light0"));

	Material material;
	material.ambient = ColorRGBAf(1, 1, 1, 1);
	material.diffuse = ColorRGBAf(1, 1, 1, 1);
	material.specular = ColorRGBAf(1, 1, 1, 1);
	material.shininess = 1.0;
	scenes[1]->addScene(objectFactory.createMaterialScene(material, "Material0"));

	renderer = std::make_unique<UI::Renderer>();

}

void World::clear()
{
	for (auto& s : scenes) {
		s->clear();
	}
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
