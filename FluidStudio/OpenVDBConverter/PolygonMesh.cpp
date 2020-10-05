#include "PolygonMesh.h"

#include "PolygonMeshImpl.h"

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
