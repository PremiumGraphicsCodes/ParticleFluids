#include "PolygonMesh.h"

#include "PolygonMeshImpl.h"
#include "Converter.h"

//#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

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

std::vector<Vector3df> PolygonMesh::getVertices() const
{
	return Converter::fromVDBf(impl->points);
}

void PolygonMesh::addTriangle(const std::array<int, 3>& indices)
{
	impl->triangles.push_back(Converter::toVDB(indices));
}

std::array<unsigned int, 3> PolygonMesh::getTriangle(const int index) const
{
	return Converter::fromVDB( impl->triangles[index] );
}

void PolygonMesh::addQuad(const std::array<int, 4>& indices)
{
	impl->quads.push_back(Converter::toVDB(indices));
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
//
//Crystal::Shape::PolygonMesh PolygonMesh::toCrystal() const
//{
//	//const auto& faces = src.get
//
//	return Crystal::Shape::PolygonMesh();
//}
//
