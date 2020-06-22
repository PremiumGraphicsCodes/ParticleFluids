#include "gtest/gtest.h"

#include "../CrystalAlgo/ZOrderCurve3d.h"

using namespace Crystal::Search;

TEST(ZOrderCurve3dTest, TestEncode)
{
	ZOrderCurve3d curve;
	EXPECT_EQ(0, curve.encode({ 0,0,0 }));
	EXPECT_EQ(1, curve.encode({ 1,0,0 }));
	EXPECT_EQ(2, curve.encode({ 0,1,0 }));
	EXPECT_EQ(3, curve.encode({ 1,1,0 }));
	EXPECT_EQ(4, curve.encode({ 0,0,1 }));
	EXPECT_EQ(5, curve.encode({ 1,0,1 }));
	EXPECT_EQ(6, curve.encode({ 0,1,1 }));
	EXPECT_EQ(7, curve.encode({ 1,1,1 }));
	EXPECT_EQ(8, curve.encode({ 2,0,0 }));
	EXPECT_EQ(9, curve.encode({ 3,0,0 }));
}