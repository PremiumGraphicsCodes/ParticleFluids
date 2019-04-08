#include "gtest/gtest.h"

#include "../Math/Line3d.h"
#include "../Math/Ray3d.h"

using namespace Crystal::Math;

TEST(Line3dTest, TestToRay)
{
	const Line3dd line(Vector3dd(0, 0, 0), Vector3dd(10, 0, 0));
	const Ray3d expected(Vector3dd(0, 0, 0), Vector3dd(1, 0, 0));
	const auto& actual = line.toRay();
	EXPECT_TRUE(expected.isSame(actual, 1.0e-12));
}