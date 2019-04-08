#include "gtest/gtest.h"

#include "../Math/Quad3d.h"

using namespace Crystal::Math;

TEST(Quad3dTest, TestIsInside)
{
	const Quad3d quad(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0), Vector3dd(0, 10, 0));
	EXPECT_TRUE( quad.isInside(Vector3dd(5, 5, 0)) );

	EXPECT_FALSE(quad.isInside(Vector3dd(11, 5, 0)));
	EXPECT_FALSE(quad.isInside(Vector3dd(-1, 5, 0)));

}