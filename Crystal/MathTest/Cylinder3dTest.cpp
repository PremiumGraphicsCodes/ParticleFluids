#include <gtest/gtest.h>

#include "../Math/Vector3d.h"
#include "../Math/Cylinder3d.h"

using namespace Crystal::Math;

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
		EXPECT_TRUE( areSame( expected, actual, 1.0e-12) );
	}


	{
		const auto& actual = cylinder.getPosition(0, 1.0);
		const Vector3dd expected(1, 0, 0.5);
		EXPECT_EQ(expected, actual);
	}
}