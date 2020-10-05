#include "PolygonMesh.h"

#include "PolygonMeshImpl.h"

using namespace Crystal::OpenVDB;

PolygonMesh::PolygonMesh() :
	impl( new PolygonMeshImpl() )
{
}

PolygonMesh::~PolygonMesh()
{
	delete impl;
}
