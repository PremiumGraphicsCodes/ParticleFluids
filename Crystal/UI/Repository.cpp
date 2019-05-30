#include "Repository.h"

#include "../Model/FileReader.h"
#include "../Model/FileExporter.h"

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

bool Repository::read(const std::string& filename)
{
	FileReader reader;
	return reader.read(filename, objects, appearances);
}

bool Repository::write(const std::string& filename)
{
	FileExporter writer;
	return writer.write(filename, objects, appearances);
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
