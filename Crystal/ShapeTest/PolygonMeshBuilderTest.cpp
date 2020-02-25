#include "pch.h"

#include "../Shape/PolygonMeshBuilder.h"

#include "../Math/Quad3d.h"
#include "../Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TEST(PolygonMeshBuilderTest, TestBuildByQuad)
{
    PolygonMeshBuilder builder;
    builder.add(Quad3d(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0)));
    EXPECT_EQ(4, builder.getPositions().size());
    EXPECT_EQ(4, builder.getTexCoords().size());
    EXPECT_EQ(1, builder.getNormals().size());
    EXPECT_EQ(2, builder.getFaces().size());
}

TEST(PolygonMeshBuilderTest, TestBuildBySphere)
{
    PolygonMeshBuilder builder;
    builder.add(Sphere3d(Vector3dd(0, 0, 0), 10.0), 2, 2);
    EXPECT_EQ(4, builder.getPositions().size());
    EXPECT_EQ(4, builder.getTexCoords().size());
    EXPECT_EQ(4, builder.getNormals().size());
    EXPECT_EQ(8, builder.getFaces().size());
}

/*
TEST(PolygonMeshBuilderTest, TestBuildBySphere)
{
    PolygonMeshBuilder builder;
    builder.add(Box3d(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10)));
    EXPECT_EQ(8, builder.getPositions().size());
    //EXPECT_EQ(24, builder.getTexCoords().size());
    EXPECT_EQ(6, builder.getNormals().size());
    EXPECT_EQ(12, builder.getFaces().size());
}
*/