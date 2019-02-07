#include "gtest/gtest.h"
#include "../Math/Matrix3d.h"

using namespace Crystal::Math;

TEST(Matrix3dTest, TestRotationMatrixX)
{
	const auto pi = Tolerance<double>::getPI();
	{
		const auto actual = rotationMatrixX(0.0);
		const auto expected = Matrix3dd
		(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, 1.0e-12));
	}

	{
		const auto actual = rotationMatrixX(0.5 * pi);
		const auto expected = Matrix3dd
		(
			1.0, 0.0, 0.0,
			0.0, 0.0,-1.0,
			0.0, 1.0, 0.0
		);
		EXPECT_TRUE( AreSame( expected, actual, 1.0e-12) );
	}

	{
		const auto actual = rotationMatrixX(pi);
		const Matrix3dd expected
		(
			1.0, 0.0, 0.0,
			0.0,-1.0, 0.0,
			0.0, 0.0,-1.0
		);
		EXPECT_TRUE(AreSame(expected, actual, 1.0e-12));
	}
}
