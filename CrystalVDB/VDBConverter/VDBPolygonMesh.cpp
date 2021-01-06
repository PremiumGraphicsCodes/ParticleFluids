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
	PolygonMeshImpl::TriangleFace triangle;
	triangle.indices = Converter::toVDB( indices );
	impl->triangles.push_back(triangle);
}

std::vector<VDBPolygonMesh::TriangleFace> VDBPolygonMesh::getTriangleFaces() const
{
	std::vector<VDBPolygonMesh::TriangleFace> faces;
	for (const auto& t : impl->triangles) {
		VDBPolygonMesh::TriangleFace face;
		face.indices = Converter::fromVDB(t.indices);
		face.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(face);
	}
	return faces;
}

void VDBPolygonMesh::addQuad(const std::array<int, 4>& indices)
{
	PolygonMeshImpl::QuadFace quad;
	quad.indices = Converter::toVDB(indices);
	impl->quads.push_back(quad);
}

std::vector<VDBPolygonMesh::QuadFace> VDBPolygonMesh::getQuadFaces() const
{
	std::vector<VDBPolygonMesh::QuadFace> faces;
	for (const auto& q : impl->quads) {
		VDBPolygonMesh::QuadFace face;
		face.indices = Converter::fromVDB(q.indices);
		face.normal = Converter::fromVDB(q.normal);
		faces.emplace_back(face);
	}
	return faces;
}

std::vector<VDBPolygonMesh::Face> VDBPolygonMesh::getAllFaces() const
{
	std::vector<VDBPolygonMesh::Face> faces;
	for (const auto& t : impl->triangles) {
		VDBPolygonMesh::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	for (const auto& t : impl->quads) {
		VDBPolygonMesh::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2], t.indices[3] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	return faces;
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