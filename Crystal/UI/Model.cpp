#include "Model.h"

#include "FileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

Model::Model()
{
}

Model::~Model()
{
	clear();
}

void Model::clear()
{
	objects.clear();
	appearances.clear();
}

bool Model::read(const std::string& filename)
{
	FileReader reader;
	return reader.read(filename);
}

bool Model::write(const std::string& filename) const
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

ViewModel3d Model::toViewModel()
{
	ViewModel3d vm;
	vm.add(objects);
	vm.add(appearances);
	return vm;
}

Box3d Model::getBoundingBox() const
{
	return objects.getBoundingBox();
}
