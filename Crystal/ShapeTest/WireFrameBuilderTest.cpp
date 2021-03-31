#include "pch.h"

#include "../Shape/WireFrameBuilder.h"

#include "../Math/Line3d.h"
#include "../Math/Box3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Circle3d.h"
#include "../Math/Cone3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TEST(WireFrameBuilderTest, TestBuildByLine)
{
	const Line3dd line(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0));

	WireFrameBuilder builder;
	builder.build(line, 1);
	EXPECT_EQ(2, builder.getPositions().size());
	EXPECT_EQ(1, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildByBox)
{
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1));

	WireFrameBuilder builder;
	builder.build(box);
	EXPECT_EQ(8, builder.getPositions().size());
	EXPECT_EQ(12, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildByCircle)
{
	const Circle3d circle(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));

	WireFrameBuilder builder;
	builder.build(circle, 2);
	EXPECT_EQ(3, builder.getPositions().size());
	EXPECT_EQ(2, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildBySphere)
{
	const Sphere3d sphere(Vector3dd(0, 0, 0), 1.0);

	WireFrameBuilder builder;
	builder.build(sphere, 9, 9);
	EXPECT_EQ(100, builder.getPositions().size());
	EXPECT_EQ(9*9*4, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildByCone)
{
	const Cone3d cone(Vector3dd(0, 0, 0), 10, 1);

	WireFrameBuilder builder;
	builder.build(cone, 9, 1);
	EXPECT_EQ(20, builder.getPositions().size());
	EXPECT_EQ(9*1*4, builder.getEdges().size());
}

TEST(WireFrameBuilderTest, TestBuildByCylinder)
{
	const Cylinder3d cylinder(1.0, 10.0, Vector3dd(0, 0, 0));

	WireFrameBuilder builder;
	builder.build(cylinder, 9, 1);
	EXPECT_EQ(20, builder.getPositions().size());
	EXPECT_EQ(9 * 1 * 4, builder.getEdges().size());
}