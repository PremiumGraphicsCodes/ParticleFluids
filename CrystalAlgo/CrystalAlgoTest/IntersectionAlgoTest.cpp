#include <gtest/gtest.h>

#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../CrystalAlgo/IntersectionAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;

TEST(IntersectionAlgoTest, TestRayAndTriangle)
{
	IntersectionAlgo algo;
	
	const Ray3d ray(Vector3dd(0,0,-10), Vector3dd(0,0,1));
	const Triangle3d triangle({ Vector3dd(-10,-10,0), Vector3dd(-10, 100, 0), Vector3dd(100, -10, 0) });
	EXPECT_TRUE( algo.calculateIntersection(ray, triangle) );
//	algo.calculateIntersection()
}