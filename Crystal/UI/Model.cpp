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
	lights.clear();
	materials.clear();
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

ViewModel3d Model::toViewModel() const
{
	ViewModel3d vm;
	const auto& particleSystems = objects.getParticleSystems();
	for (const auto& p : particleSystems) {
		vm.add(p);
	}
	const auto& wires = objects.getWireFrames();
	for (const auto& w : wires) {
		vm.add(w);
	}
	const auto& polygons = objects.getPolygonMeshes();
	for (const auto& p : polygons) {
		vm.add(p);
	}

	return vm;
}

Box3d Model::getBoundingBox() const
{
	return objects.getBoundingBox();
}
