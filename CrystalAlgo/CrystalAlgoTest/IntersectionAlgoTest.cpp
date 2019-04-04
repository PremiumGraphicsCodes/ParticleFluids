#include <gtest/gtest.h>

#include "../../Crystal/Math/Plane3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../CrystalAlgo/IntersectionAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;

TEST(IntersectionAlgoTest, TestLineAndSphere)
{
	IntersectionAlgo algo;
//	algo.calculateIntersection()
}

TEST(IntersectionAlgoTest, TestRayAndPlane)
{
	IntersectionAlgo algo;
	const Ray3d ray(Vector3dd(0, 0, -1), Vector3dd(0, 0, 1));

	{
		const Plane3d plane(Vector3dd(0, 0, 0), Vector3dd(0, 0, 1));
		EXPECT_FALSE(algo.calculateIntersection(ray, plane));
		EXPECT_TRUE(algo.getIntersections().empty());
	}

	{
		const Plane3d plane(Vector3dd(0, 0, 0), Vector3dd(0, 0, -1));
		EXPECT_TRUE(algo.calculateIntersection(ray, plane));
		const auto& intersections = algo.getIntersections();
		EXPECT_EQ(1, intersections.size());
		const auto i = intersections[0];
		EXPECT_EQ(Vector3dd(0, 0, 0), i.position);
		EXPECT_EQ(Vector3dd(0, 0,-1), i.normal);
	}

	//	algo.calculateIntersection()
}

TEST(IntersectionAlgoTest, TestRayAndTriangle)
{
	IntersectionAlgo algo;
	
	const Ray3d ray(Vector3dd(0,0,-10), Vector3dd(0,0,1));
	const Triangle3d triangle({ Vector3dd(-10,-10,0), Vector3dd(-10, 100, 0), Vector3dd(100, -10, 0) });
	EXPECT_TRUE( algo.calculateIntersection(ray, triangle) );
//	algo.calculateIntersection()
}