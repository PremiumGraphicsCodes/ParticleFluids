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
	Graphics::PointLight* light = new Graphics::PointLight();
	light->setPosition(glm::vec3(100, 100, 100));
	light->setAmbient(glm::vec4(1, 1, 1, 1));
	light->setDiffuse(glm::vec4(1, 1, 1, 1));
	light->setSpecular(glm::vec4(1, 1, 1, 1));
	objects.addScene(objectFactory.createLightScene(light, "Light"));
}

Repository::~Repository()
{
	clear();
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
	objects.addViewModel(vm.object);
	items.addViewModel(vm.object);

	objects.addViewModel(vm.objectId);

	return vm;
}

Box3d Repository::getBoundingBox() const
{
	return objects.getBoundingBox();
}
