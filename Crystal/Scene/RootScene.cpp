#include "RootScene.h"

#include "../Scene/FileImporter.h"
#include "../Scene/FileExporter.h"

#include "PointShaderScene.h"
#include "TextureScene.h"

#include "SceneBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

RootScene::RootScene() :
	objects(0, "Root"),
	items(0, "Item"),
	shaders(0, "Shaders")
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

	shaders.addChild(new PointShaderScene(1, "PointShader"));

	shaders.addChild(new TextureScene(2, "OnScreenTexture", Image(512, 512)));

	Image image2(2, 2);
	image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
	image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
	image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
	shaders.addChild(new TextureScene(3, "SmoothTexture", image2));

	shaders.addChild(new TextureScene(4, "IdTexture", Image(512, 512)));

	//shaders.build();
}

void RootScene::clear()
{
	objects.clear();
	//shaders.clear();
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
