#include <gtest/gtest.h>

#include "../Math/Vector3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;

namespace {
	double tolerance = 1.0e-12;
}

TEST(Cylinder3dTest, TestGetPosition)
{
	const Cylinder3d cylinder;

	{
		const auto& actual = cylinder.getPosition(0, 0);
		const Vector3dd expected(1, 0, -0.5);
		EXPECT_EQ(expected, actual);
	}

	{
		const auto& actual = cylinder.getPosition(0.5, 0);
		const Vector3dd expected(-1, 0, -0.5);
		EXPECT_TRUE( areSame( expected, actual, tolerance) );
	}

	{
		const auto& actual = cylinder.getPosition(0, 1.0);
		const Vector3dd expected(1, 0, 0.5);
		EXPECT_EQ(expected, actual);
	}
}