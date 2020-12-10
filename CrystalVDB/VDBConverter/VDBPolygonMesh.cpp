#include "VDBPolygonMesh.h"

#include "PolygonMeshImpl.h"
#include "Converter.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

VDBPolygonMesh::VDBPolygonMesh() :
	impl( new PolygonMeshImpl() )
{
}

//PolygonMesh::PolygonMesh(PolygonMesh&& rhs) = default;

//PolygonMesh& PolygonMesh::operator=(const PolygonMesh&& rhs) = default;

VDBPolygonMesh::~VDBPolygonMesh()
{
	delete impl;
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


//void PolygonMesh::fromCrystal(const Crystal::Shape::PolygonMesh& src)
//{	
//	impl->points = Converter::toVDB(src.getPositions());
//	const auto faces = src.getFaces();
//	for (const auto& f : faces) {
//		addTriangle( f.getVertexIds() );
//	}
//	/*
//	const auto& faces = src.getFaces();
//	for (const auto& f : faces) {
//		impl->triangles.push_back()
//	}
//	*/
//	return;
//}

std::unique_ptr<Crystal::Shape::PolygonMesh> VDBPolygonMesh::toCrystal() const
{
	auto mesh = std::make_unique<Crystal::Shape::PolygonMesh>();

	auto vertices = this->getVerticesd();

	auto triangles = this->getTriangles();
	auto quads = this->getQuads();

	Crystal::Shape::PolygonMeshBuilder builder;

	int normalId = builder.createNormal(Vector3dd(0, 0, 1));
	for (const auto& v : vertices) {
		int id = builder.createPosition(v);
		builder.createVertex(id, normalId);
	}

	for (const auto& t : triangles) {
		builder.createFace(t[0], t[1], t[2]);
	}

	for (const auto& t : quads) {
		builder.createFace(t[0], t[1], t[2]);
		//builder.createFace(v3, v2, v1);
	}

	mesh->positions = builder.getPositions();
	mesh->normals = builder.getNormals();
	mesh->vertices = builder.getVertices();
	mesh->faces = builder.getFaces();

	return std::move(mesh);

	//return Crystal::Shape::PolygonMesh();
}



