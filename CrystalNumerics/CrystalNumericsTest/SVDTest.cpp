#include "pch.h"

#include "gtest/gtest.h"
#include "../CrystalNumerics/SVD.h"

using namespace Crystal::Math;
using namespace Crystal::Numerics;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TEST(SVDTest, TestSolve2x2)
{
	{
		Matrix2dd m(1, 2, 2, 3);
		SVD svd;
		const auto actual = svd.calculate(m);
		const auto values = actual.eigenValues;
		EXPECT_FLOAT_EQ(-0.23606804013252258, values[0]);
		EXPECT_FLOAT_EQ(4.2360687255859375, values[1]);
	}
	{
		Matrix2dd m = rotationMatrixX(0.5 * PI);
		SVD svd;
		const auto actual = svd.calculate(m);
		const auto values = actual.eigenValues;
		EXPECT_NEAR( 0.0, values[0], tolerance);
		EXPECT_NEAR( 1.0, values[1], tolerance);
	}
	{
		Matrix2dd m = rotationMatrixY(0.5 * PI);
		SVD svd;
		const auto actual = svd.calculate(m);
		const auto values = actual.eigenValues;
		EXPECT_NEAR( 0.0, values[0], tolerance);
		EXPECT_NEAR( 1.0, values[1], tolerance);
	}
}

TEST(SVDTest, TestSolve3x3)
{
	Matrix3dd m = rotationMatrixX(PI);
	SVD svd;
	const auto actual = svd.calculate(m);
	EXPECT_FLOAT_EQ(-1.0, actual[0]);
	EXPECT_FLOAT_EQ(-1.0, actual[1]);
	EXPECT_FLOAT_EQ( 1.0, actual[2]);
}