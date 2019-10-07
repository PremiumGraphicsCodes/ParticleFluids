#include "pch.h"
#include <gtest/gtest.h>

#include "../../Crystal/Math/Line3d.h"
#include "../../Crystal/Math/Plane3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../CrystalAlgo/IntersectionAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;

namespace {
	Triangle3d getTriangle()
	{
		return Triangle3d({ Vector3dd(0,0,0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0) });
	}
}

TEST(IntersectionAlgoTest, TestLineAndTriangle)
{
	const auto tolerance = 1.0e-12;
	const auto& triangle = getTriangle();
	IntersectionAlgo algo;

	{
		const Line3dd line(Vector3dd(1, 1, -1), Vector3dd(0, 0, 2));
		EXPECT_FALSE(algo.calculateIntersection(line, triangle, tolerance));
	}

	{
		const Line3dd line(Vector3dd(1, 1, 1), Vector3dd(0, 0, -2));
		EXPECT_TRUE(algo.calculateIntersection(line, triangle, tolerance));
		const auto& intersections = algo.getIntersections();
		EXPECT_EQ(1, intersections.size());
		const auto i = intersections[0];
		EXPECT_EQ(Vector3dd(1, 1, 0), i.position);
		EXPECT_EQ(Vector3dd(0, 0, 1), i.normal);
	}
}

TEST(IntersectionAlgoTest, TestRayAndPlane)
{
	const auto tolerance = 1.0e-12;

	IntersectionAlgo algo;
	const Ray3d ray(Vector3dd(0, 0, -1), Vector3dd(0, 0, 1));

	{
		const Plane3d plane(Vector3dd(0, 0, 0), Vector3dd(0, 0, 1));
		EXPECT_FALSE(algo.calculateIntersection(ray, plane, tolerance));
		EXPECT_TRUE(algo.getIntersections().empty());
	}

	{
		const Plane3d plane(Vector3dd(0, 0, 0), Vector3dd(0, 0, -1));
		EXPECT_TRUE(algo.calculateIntersection(ray, plane, tolerance));
		const auto& intersections = algo.getIntersections();
		EXPECT_EQ(1, intersections.size());
		const auto i = intersections[0];
		EXPECT_EQ(Vector3dd(0, 0, 0), i.position);
		EXPECT_EQ(Vector3dd(0, 0,-1), i.normal);
	}
}

TEST(IntersectionAlgoTest, TestRayAndTriangle)
{
	const auto tolerance = 1.0e-12;

	IntersectionAlgo algo;
	const auto& triangle = getTriangle();

	{
		const Ray3d ray(Vector3dd(1, 1,-1), Vector3dd(0, 0, 1));
		EXPECT_FALSE(algo.calculateIntersection(ray, triangle, tolerance));
	}

	{
		const Ray3d ray(Vector3dd(1, 1, 1), Vector3dd(0, 0, -1));
		EXPECT_TRUE(algo.calculateIntersection(ray, triangle, tolerance));
		const auto& intersections = algo.getIntersections();
		EXPECT_EQ(1, intersections.size());
		const auto i = intersections[0];
		EXPECT_EQ(Vector3dd(1, 1, 0), i.position);
		EXPECT_EQ(Vector3dd(0, 0, 1), i.normal);
	}
}

TEST(IntersectionAlgoTest, TestTriangleAndTriangle)
{
	const auto tolerance = 1.0e-12;
	IntersectionAlgo algo;
	const auto& triangle1 = getTriangle();

	{
		const  Triangle3d triangle2({ Vector3dd(10,0,0), Vector3dd(20, 0, 0), Vector3dd(10, 20, 0) });
		EXPECT_FALSE(algo.calculateIntersection(triangle1, triangle2, tolerance));
	}

	{
		const  Triangle3d triangle2({ Vector3dd(5,0,-10), Vector3dd(5, 0, 10), Vector3dd(0, 10, 0) });
		EXPECT_TRUE(algo.calculateIntersection(triangle1, triangle2, tolerance));
	}

}