#include "VDBPolygonMesh.h"

#include "PolygonMeshImpl.h"
#include "Converter.h"

#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPolygonMesh::VDBPolygonMesh() :
	VDBPolygonMesh(-1, "")
{
}

VDBPolygonMesh::VDBPolygonMesh(const int id, const std::string& name) :
	IShapeScene(id, name)
{
	impl = std::make_unique<PolygonMeshImpl>();
	presenter = std::make_unique<VDBPolygonMeshPresenter>(this);
}

VDBPolygonMesh::~VDBPolygonMesh()
{

}

void VDBPolygonMesh::addVertex(const Vector3df& position)
{
	impl->points.push_back(Converter::toVDB(position));
}

Vector3df VDBPolygonMesh::getVertex(const int index)
{
	return Converter::fromVDB( impl->points[index] );
}

std::vector<Vector3df> VDBPolygonMesh::getVerticesf() const
{
	return Converter::fromVDBf<Vector3df>(impl->points);
}

std::vector<Vector3dd> VDBPolygonMesh::getVerticesd() const
{
	return Converter::fromVDBf<Vector3dd>(impl->points);
}

void VDBPolygonMesh::addTriangle(const std::array<int, 3>& indices)
{
	impl->triangles.push_back(Converter::toVDB(indices));
}

std::vector<std::array<unsigned int, 3>> VDBPolygonMesh::getTriangles() const
{
	std::vector<std::array<unsigned int, 3>> dest;
	for (const auto& t : impl->triangles) {
		dest.push_back(Converter::fromVDB(t));
	}
	return dest;
}

void VDBPolygonMesh::addQuad(const std::array<int, 4>& indices)
{
	impl->quads.push_back(Converter::toVDB(indices));
}

std::vector<std::array<unsigned int, 4>> VDBPolygonMesh::getQuads() const
{
	std::vector<std::array<unsigned int, 4>> dest;
	for (const auto& q : impl->quads) {
		dest.push_back(Converter::fromVDB(q));
	}
	return dest;
}

Box3d VDBPolygonMesh::getBoundingBox() const
{
	if (impl->points.empty()) {
		return Box3d::createDegeneratedBox();
	}
	auto vertices = this->getVerticesd();

	Math::Box3d box(vertices[0]);
	for (auto v : vertices) {
		box.add(v);
	}
	return box;
}