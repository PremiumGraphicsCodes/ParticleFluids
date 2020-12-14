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

namespace {
	Vector3dd getNormal(const std::vector<Vector3dd>& positions, const int p0, const int p1, const int p2)
	{
		const auto& v0 = positions[p0];
		const auto& v1 = positions[p1];
		const auto& v2 = positions[p2];
		const auto normal = glm::cross(glm::normalize(v2 - v1), glm::normalize(v0 - v1));
		return normal;
	}
}

std::unique_ptr<Crystal::Shape::PolygonMesh> VDBPolygonMesh::toCrystal() const
{
	auto mesh = std::make_unique<Crystal::Shape::PolygonMesh>();

	auto vertices = this->getVerticesd();

	auto triangles = this->getTriangles();
	auto quads = this->getQuads();

	Crystal::Shape::PolygonMeshBuilder builder;

	for (const auto& v : vertices) {
		int id = builder.createPosition(v);
//		builder.createVertex(id, normalId);
	}

	for (const auto& t : triangles) {
		builder.createFace(t[0], t[1], t[2]);
	}

	for (const auto& t : quads) {
		{
			const auto normal = ::getNormal(vertices, t[0], t[1], t[2]);
			const auto normalId = builder.createNormal(normal);
			const auto v00 = builder.createVertex(t[0], normalId);
			const auto v01 = builder.createVertex(t[1], normalId);
			const auto v02 = builder.createVertex(t[2], normalId);
			builder.createFace(v00, v01, v02);
		}
		{
			const auto normal = ::getNormal(vertices, t[2], t[3], t[0]);
			const auto normalId = builder.createNormal(normal);
			const auto v00 = builder.createVertex(t[2], normalId);
			const auto v01 = builder.createVertex(t[3], normalId);
			const auto v02 = builder.createVertex(t[0], normalId);
			builder.createFace(v00, v01, v02);
		}
	}

	mesh->positions = builder.getPositions();
	mesh->normals = builder.getNormals();
	mesh->vertices = builder.getVertices();
	mesh->faces = builder.getFaces();

	return std::move(mesh);

	//return Crystal::Shape::PolygonMesh();
}



