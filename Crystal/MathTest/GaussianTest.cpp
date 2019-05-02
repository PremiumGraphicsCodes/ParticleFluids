#include "gtest/gtest.h"

#include "../Math/Gaussian.h"

using namespace Crystal::Math;

TEST(GaussianTest, TestGetValue)
{
	Gaussian gaussian;
	const auto v0 = gaussian.getValue(0.0);
	const auto v1 = gaussian.getValue(1.0);
	EXPECT_GE(v0, v1);
	//const auto expected = 
}