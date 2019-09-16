#include "World.h"

#include "PointRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

World::World() :
	objects(0, "Root"),
	items(0, "Item")
{
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
	objects.addScene(objectFactory.createLightScene(light, "Light0"));
}

void World::clear()
{
	objects.clear();
	//shaders.clear();
}

void World::updateViewModel()
{
	ViewModel vm;
	objects.toViewModel(vm.object);
	objects.toIdViewModel(vm.objectId);

	items.toViewModel(vm.object);

	this->viewModel = vm;
}

Box3d World::getBoundingBox() const
{
	return objects.getBoundingBox();
}
