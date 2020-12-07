#include "PolygonMesh.h"

#include "PolygonMeshImpl.h"
#include "Converter.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

PolygonMesh::PolygonMesh() :
	impl( new PolygonMeshImpl() )
{
}

//PolygonMesh::PolygonMesh(PolygonMesh&& rhs) = default;

//PolygonMesh& PolygonMesh::operator=(const PolygonMesh&& rhs) = default;

PolygonMesh::~PolygonMesh()
{
	delete impl;
}

void PolygonMesh::addVertex(const Vector3df& position)
{
	impl->points.push_back(Converter::toVDB(position));
}

Vector3df PolygonMesh::getVertex(const int index)
{
	return Converter::fromVDB( impl->points[index] );
}

std::vector<Vector3df> PolygonMesh::getVerticesf() const
{
	return Converter::fromVDBf<Vector3df>(impl->points);
}

std::vector<Vector3dd> PolygonMesh::getVerticesd() const
{
	return Converter::fromVDBf<Vector3dd>(impl->points);
}

void PolygonMesh::addTriangle(const std::array<int, 3>& indices)
{
	impl->triangles.push_back(Converter::toVDB(indices));
}

std::vector<std::array<unsigned int, 3>> PolygonMesh::getTriangles() const
{
	std::vector<std::array<unsigned int, 3>> dest;
	for (const auto& t : impl->triangles) {
		dest.push_back(Converter::fromVDB(t));
	}
	return dest;
}

void PolygonMesh::addQuad(const std::array<int, 4>& indices)
{
	impl->quads.push_back(Converter::toVDB(indices));
}

std::vector<std::array<unsigned int, 4>> PolygonMesh::getQuads() const
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

Crystal::Shape::PolygonMesh* PolygonMesh::toCrystal() const
{
	auto mesh = new Crystal::Shape::PolygonMesh();

	auto vertices = this->getVerticesd();

	auto triangles = this->getTriangles();

	mesh->positions = vertices;

	/*
	impl->points.push_back()

	const auto& triangles = impl->triangles;
	for (const auto t : triangles) {
		const auto v1 = t[0];
		const auto v2 = t[1];
		const auto v3 = t[2];
		Crystal::Shape::Vertex vertex;
		vertex.positionId = ;
		mesh->vertices
	}
	mesh->vertices[]
	*/

	return mesh;

	//return Crystal::Shape::PolygonMesh();
}

