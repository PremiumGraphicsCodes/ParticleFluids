#include "gtest/gtest.h"

#include "../Math/Plane3d.h"

using namespace Crystal::Math;

TEST(Plane3dTest, TestGetDistance)
{
	const Plane3d plane(Vector3dd(0, 0, 0), Vector3dd(0, 0, 1));
	EXPECT_DOUBLE_EQ(10.0, plane.getDistance(Vector3dd(0, 0, 10)));
}