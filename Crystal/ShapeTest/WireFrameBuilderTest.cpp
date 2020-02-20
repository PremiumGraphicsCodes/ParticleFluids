#include "pch.h"

#include "../Shape/WireFrameBuilder.h"

#include "../Math/Line3d.h"
#include "../Math/Box3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Cone3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TEST(WireFrameBuilderTest, TestBuildByLine)
{
	WireFrameBuilder builder;
	builder.build(Line3dd(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0)));
	EXPECT_EQ(2, builder.getPositions().size());
	EXPECT_EQ(1, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildByBox)
{
	WireFrameBuilder builder;
	builder.build(Box3d(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1)));
	EXPECT_EQ(8, builder.getPositions().size());
	EXPECT_EQ(12, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildBySphere)
{
	WireFrameBuilder builder;
	builder.build(Sphere3d(Vector3dd(0,0,0), 1.0), 10, 10);
	EXPECT_EQ(100, builder.getPositions().size());
}

TEST(WireFrameBuilderTest, TestBuildByCone)
{
	WireFrameBuilder builder;
	const Cone3d cone(Vector3dd(0, 0, 0), 10, 10);
	builder.build(cone, 10);
	EXPECT_EQ(10+1, builder.getPositions().size());
}

TEST(WireFrameBuilderTest, TestBuildByCylinder)
{
	WireFrameBuilder builder;
	const Cylinder3d cylinder(1.0, 10.0, Vector3dd(0, 0, 0));
	builder.build(cylinder, 12);
	EXPECT_EQ(24+2, builder.getPositions().size());
}