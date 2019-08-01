#include "RootScene.h"

#include "../Scene/FileImporter.h"
#include "../Scene/FileExporter.h"

#include "SceneBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

RootScene::RootScene() :
	objects(0, "Root"),
	items(0, "Item")
{
}

RootScene::~RootScene()
{
	clear();
}

void RootScene::init()
{
	SceneBuilder builder(objects, objectFactory);
	builder.build();
}

void RootScene::clear()
{
	objects.clear();
}

bool RootScene::importFile(const std::experimental::filesystem::path& filename)
{
	FileImporter reader;
	return reader.importFile(filename, &objects, &objectFactory);
}

bool RootScene::exportFile(const std::experimental::filesystem::path& filename)
{
	FileExporter writer;
	return writer.exportFile(filename, objects);
}

ViewModel RootScene::toViewModel()
{
	ViewModel vm;
	vm.object = objects.toViewModel();
	vm.object.merge(items.toViewModel());

	vm.objectId = objects.toIdViewModel();

	return vm;
}

Box3d RootScene::getBoundingBox() const
{
	return objects.getBoundingBox();
}
