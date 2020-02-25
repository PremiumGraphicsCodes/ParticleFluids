#include "gtest/gtest.h"

#include "../Math/Circle3d.h"

using namespace Crystal::Math;

TEST(Circle3dTest, TestGetNormal)
{
	const Circle3d circle(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));
	EXPECT_TRUE( areSame(Vector3dd(0,0,1), circle.getNormal()) );
}