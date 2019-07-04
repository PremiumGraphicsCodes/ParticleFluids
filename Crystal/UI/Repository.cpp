#include "Repository.h"

#include "../Scene/FileImporter.h"
#include "../Scene/FileExporter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
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

void Repository::clear()
{
	objects.clear();
}

bool Repository::importFile(const std::experimental::filesystem::path& filename)
{
	FileImporter reader;
	return reader.importFile(filename, objects);
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
