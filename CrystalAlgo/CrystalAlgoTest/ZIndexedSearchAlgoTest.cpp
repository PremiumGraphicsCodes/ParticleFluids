#include "../CrystalAlgo/ZIndexedSearchAlgo.h"

#include "gtest/gtest.h"

using namespace Crystal::Search;

TEST(ZIndexedSearchAlgoTest, TestToIndex1d)
{
	ZIndexedSearchAlgo algo;
	EXPECT_EQ(0, algo.toIndex1d(0, 0, 0));
	EXPECT_EQ(1, algo.toIndex1d(1, 0, 0));
}