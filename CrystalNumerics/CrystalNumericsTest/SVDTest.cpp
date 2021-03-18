#include "pch.h"

#include "gtest/gtest.h"
#include "../CrystalNumerics/SVD.h"

using namespace Crystal::Math;
using namespace Crystal::Numerics;

TEST(SVDTest, TestSolve2x2)
{
	Matrix2dd m(1, 2, 2, 3);
	SVD svd;
	const auto actual = svd.calculate(m);
	EXPECT_FLOAT_EQ(-0.23606804013252258, actual[0]);
	EXPECT_FLOAT_EQ(4.2360687255859375, actual[1]);
	//EXPECT_EQ(1, 1);
	//EXPECT_TRUE(true);
}