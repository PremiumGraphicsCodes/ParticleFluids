#include "IModel.h"

#include "FileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

IModel::IModel()
{
}

IModel::~IModel()
{
	clear();
}

void IModel::clear()
{
	objects.clear();
	lights.clear();
}

bool IModel::read(const std::string& filename)
{
	FileReader reader;
	return reader.read(filename);
}

bool IModel::write(const std::string& filename) const
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

ViewModel3d IModel::toViewModel() const
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

Box3d IModel::getBoundingBox() const
{
	return objects.getBoundingBox();
}
