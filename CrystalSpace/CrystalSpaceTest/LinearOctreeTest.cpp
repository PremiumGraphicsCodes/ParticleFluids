#include <gtest/gtest.h>

#include "../CrystalSpace/LinearOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(LinearOctreeTest, TestInit)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	{
		LinearOctreeOperator treeOperator;
		treeOperator.init(space, 0);
		EXPECT_EQ(treeOperator.getTable().size(), 1);
	}

	{
		LinearOctreeOperator treeOperator;
		treeOperator.init(space, 1);
		EXPECT_EQ(treeOperator.getTable().size(), 9);
	}

	{
		LinearOctreeOperator treeOperator;
		treeOperator.init(space, 2);
		EXPECT_EQ(treeOperator.getTable().size(), 73);
	}

	//treeOperator.
}

TEST(LinearOctreeTest, TestCalculateSpace)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctreeOperator treeOperator;
	treeOperator.init(space, 2);
	const auto bb = treeOperator.calculateAABBFromMortonNumber(0);
	EXPECT_TRUE(bb.isSame(space, 1.0e-12));
	const auto bb2 = treeOperator.calculateAABBFromMortonNumber(1);
	const Box3dd expected2(Vector3dd(0, 0, 0), Vector3dd(5, 5, 5));
	EXPECT_TRUE(bb2.isSame(expected2, 1.0e-12));

	const auto bb3 = treeOperator.calculateAABBFromMortonNumber(2);
	const Box3dd expected3(Vector3dd(5, 0, 0), Vector3dd(10, 5, 5));
	//EXPECT_TRUE(bb2.isSame(expected2, 1.0e-12));

}