#include <gtest/gtest.h>

#include "../CrystalSpace/LinearOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

TEST(LinearOctreeTest, Test)
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