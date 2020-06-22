#include "gtest/gtest.h"

#include "../CrystalAlgo/ZOrderCurve.h"

using namespace Crystal::Search;

TEST(ZOrderCurve2dTest, TestEncode)
{
	EXPECT_EQ(0, ZOrderCurve2d::encode({ 0,0 }));
	EXPECT_EQ(1, ZOrderCurve2d::encode({ 1,0 }));
	EXPECT_EQ(2, ZOrderCurve2d::encode({ 0,1 }));
	EXPECT_EQ(3, ZOrderCurve2d::encode({ 1,1 }));
	EXPECT_EQ(4, ZOrderCurve2d::encode({ 2,0 }));
	EXPECT_EQ(5, ZOrderCurve2d::encode({ 3,0 }));
	EXPECT_EQ(6, ZOrderCurve2d::encode({ 2,1 }));
	EXPECT_EQ(7, ZOrderCurve2d::encode({ 3,1 }));
	EXPECT_EQ(8, ZOrderCurve2d::encode({ 0,2 }));
	EXPECT_EQ(9, ZOrderCurve2d::encode({ 1,2 }));
}

TEST(ZOrderCurve3dTest, TestEncode)
{
	EXPECT_EQ(0, ZOrderCurve3d::encode({ 0,0,0 }));
	EXPECT_EQ(1, ZOrderCurve3d::encode({ 1,0,0 }));
	EXPECT_EQ(2, ZOrderCurve3d::encode({ 0,1,0 }));
	EXPECT_EQ(3, ZOrderCurve3d::encode({ 1,1,0 }));
	EXPECT_EQ(4, ZOrderCurve3d::encode({ 0,0,1 }));
	EXPECT_EQ(5, ZOrderCurve3d::encode({ 1,0,1 }));
	EXPECT_EQ(6, ZOrderCurve3d::encode({ 0,1,1 }));
	EXPECT_EQ(7, ZOrderCurve3d::encode({ 1,1,1 }));
	EXPECT_EQ(8, ZOrderCurve3d::encode({ 2,0,0 }));
	EXPECT_EQ(9, ZOrderCurve3d::encode({ 3,0,0 }));
}