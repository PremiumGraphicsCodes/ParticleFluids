#include "Repository.h"

#include "FileReader.h"

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
	return reader.read(filename);
}

bool Repository::write(const std::string& filename) const
{
	//const auto& ext = std::experimental::filesystem::path(filename).extension();
	/*
	if (ext == ".obj") {
		OBJFileWriter reader;
		return reader.read(filename);
	}
	*/
	return false;
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
