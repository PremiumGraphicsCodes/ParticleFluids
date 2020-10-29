#include "gtest/gtest.h"

#include "../VDBConverter/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(PolygonMeshTest, TestGetVertex)
{
	PolygonMesh mesh;
	mesh.addVertex(Vector3df(0, 0, 0));
	mesh.addVertex(Vector3df(1, 0, 0));
	mesh.addVertex(Vector3df(1, 1, 0));
//	mesh.addTriangle({ 0, 1, 2 });

	EXPECT_EQ( Vector3df(0,0,0), mesh.getVertex(0));
	EXPECT_EQ( Vector3df(1,0,0), mesh.getVertex(1));
	EXPECT_EQ( Vector3df(1,1,0), mesh.getVertex(2));
	//mesh.getTriangle(0);
}