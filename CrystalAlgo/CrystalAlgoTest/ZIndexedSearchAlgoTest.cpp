#include "../CrystalAlgo/ZIndexedSearchAlgo.h"

#include "gtest/gtest.h"

using namespace Crystal::Search;

TEST(ZIndexedSearchAlgoTest, TestToIndex1d)
{
	ZIndexedSearchAlgo algo;
	EXPECT_EQ(0, algo.toIndex1d(0, 0, 0));
	EXPECT_EQ(1, algo.toIndex1d(1, 0, 0));
	EXPECT_EQ(2, algo.toIndex1d(0, 1, 0));
	EXPECT_EQ(3, algo.toIndex1d(1, 1, 0));

	EXPECT_EQ(4, algo.toIndex1d(2, 0, 0));
	EXPECT_EQ(5, algo.toIndex1d(3, 0, 0));
}