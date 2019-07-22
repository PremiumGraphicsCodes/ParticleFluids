#include "Repository.h"

#include "../Scene/FileImporter.h"
#include "../Scene/FileExporter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Repository::Repository() :
	objects(0, "Root"),
	items(0, "Item")
{
}

Repository::~Repository()
{
	clear();
}

void Repository::init()
{
	Graphics::PointLight light;
	light.setPosition(glm::vec3(100, 100, 100));
	light.setAmbient(glm::vec4(1, 1, 1, 1));
	light.setDiffuse(glm::vec4(1, 1, 1, 1));
	light.setSpecular(glm::vec4(1, 1, 1, 1));
	objects.addScene(objectFactory.createLightScene(light, "Light"));

	objects.addScene(objectFactory.createTextureScene(Image(512, 512), "OnScreenTexture"));

	Image image2(2, 2);
	image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
	image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
	image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
	image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
	objects.addScene(objectFactory.createTextureScene(image2, "SmoothTexture"));

	objects.addScene(objectFactory.createTextureScene(Image(512, 512), "IdTexture"));
}

void Repository::clear()
{
	objects.clear();
}

bool Repository::importFile(const std::experimental::filesystem::path& filename)
{
	FileImporter reader;
	return reader.importFile(filename, &objects, &objectFactory);
}

bool Repository::exportFile(const std::experimental::filesystem::path& filename)
{
	FileExporter writer;
	return writer.exportFile(filename, objects);
}

ViewModel Repository::toViewModel()
{
	ViewModel vm;
	vm.object = objects.toViewModel();
	vm.object.merge( items.toViewModel() );

	vm.objectId = objects.toIdViewModel();

	return vm;
}

Box3d Repository::getBoundingBox() const
{
	return objects.getBoundingBox();
}
