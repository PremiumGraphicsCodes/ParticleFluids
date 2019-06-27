#include "Repository.h"

#include "../Scene/FileImporter.h"
#include "../Scene/FileExporter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

Repository::Repository()
{
}

Repository::~Repository()
{
	clear();
}

void Repository::clear()
{
	objects.clear();
	appearances.clear();
}

bool Repository::importFile(const std::experimental::filesystem::path& filename)
{
	FileImporter reader;
	return reader.importFile(filename, objects, appearances);
}

bool Repository::exportFile(const std::experimental::filesystem::path& filename)
{
	FileExporter writer;
	return writer.exportFile(filename, objects, appearances);
}

ViewModel Repository::toViewModel()
{
	ViewModel vm;
	vm.object.add(objects, *appearances.getMaterials());
	vm.objectId.add(objects);
	vm.appearance.add(appearances);
	vm.object.add(items, *appearances.getMaterials());
	return vm;
}

Box3d Repository::getBoundingBox() const
{
	return objects.getBoundingBox();
}
