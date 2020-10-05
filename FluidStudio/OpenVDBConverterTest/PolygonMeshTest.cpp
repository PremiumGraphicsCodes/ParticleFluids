#include "gtest/gtest.h"

#include "../OpenVDBConverter/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

TEST(PolygonMeshTest, Test)
{
	PolygonMesh mesh;
	mesh.addVertex(Vector3dd(1,2,3));
}