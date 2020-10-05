#include "PolygonMesh.h"

#include "PolygonMeshImpl.h"
#include "Converter.h"

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

void PolygonMesh::addVertex(const Vector3dd& position)
{
	impl->points.push_back(Converter::toVDB(position));
}

void PolygonMesh::addTriangle(const std::array<int, 3>& indices)
{
	openvdb::Vec3I i(indices[0], indices[1], indices[2]);
	impl->triangles.push_back(i);
}

void PolygonMesh::addQuad(const std::array<int, 4>& indices)
{
	openvdb::Vec4I i(indices[0], indices[1], indices[2], indices[3]);
	impl->quads.push_back(i);
}
