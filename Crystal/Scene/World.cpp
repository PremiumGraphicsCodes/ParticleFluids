#include "World.h"

#include "../Scene/FileImporter.h"
#include "../Scene/FileExporter.h"

#include "PointShaderScene.h"
#include "TextureScene.h"

#include "SceneBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

World::World() :
	objects(0, "Root"),
	items(0, "Item"),
	shaders(0, "Shaders")
{
}

World::~World()
{
	clear();
}

void World::init()
{
	SceneBuilder builder(objects, objectFactory);
	builder.build();
}

void World::clear()
{
	objects.clear();
	//shaders.clear();
}

bool World::importFile(const std::experimental::filesystem::path& filename)
{
	FileImporter reader;
	return reader.importFile(filename, &objects, &objectFactory);
}

bool World::exportFile(const std::experimental::filesystem::path& filename)
{
	FileExporter writer;
	return writer.exportFile(filename, objects);
}

void World::updateViewModel()
{
	ViewModel vm;
	vm.object = objects.toViewModel();
	vm.object.merge(items.toViewModel());

	vm.objectId = objects.toIdViewModel();

	this->viewModel = vm;
}

Box3d World::getBoundingBox() const
{
	return objects.getBoundingBox();
}
