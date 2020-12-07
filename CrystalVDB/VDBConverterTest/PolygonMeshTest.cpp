#include "gtest/gtest.h"

#include "../../Crystal/Shape/PolygonMesh.h"

#include "../VDBConverter/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(PolygonMeshTest, TestToCrystal)
{
	PolygonMesh mesh;
	mesh.addVertex(Vector3df(0, 0, 0));
	mesh.addVertex(Vector3df(1, 0, 0));
	mesh.addVertex(Vector3df(1, 1, 0));
	mesh.addTriangle({ 0, 1, 2 });

	EXPECT_EQ(Vector3df(0, 0, 0), mesh.getVertex(0));
	EXPECT_EQ(Vector3df(1, 0, 0), mesh.getVertex(1));
	EXPECT_EQ(Vector3df(1, 1, 0), mesh.getVertex(2));
	auto dest = mesh.toCrystal();
	const auto positions = dest->getPositions();
	EXPECT_EQ(3, positions.size());
	const auto faces = dest->getFaces();
	EXPECT_EQ(1, faces.size());
}