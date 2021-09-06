#include <gtest/gtest.h>

#include "../CrystalSpace/LinearOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

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

TEST(LinearOctreeTest, TestCalculateAABBFromMotonNumber)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));

	LinearOctreeOperator treeOperator;
	treeOperator.init(space, 2);

	const auto expected0 = space;
	const auto bb0 = treeOperator.calculateAABBFromMortonNumber(0);
	EXPECT_TRUE(bb0.isSame(expected0, tolerance));

	const Box3dd expected1(Vector3dd(0, 0, 0), Vector3dd(5, 5, 5));
	const auto bb1 = treeOperator.calculateAABBFromMortonNumber(1);
	EXPECT_TRUE(bb1.isSame(expected1, tolerance));

	const Box3dd expected2(Vector3dd(5, 0, 0), Vector3dd(10, 5, 5));
	const auto bb2 = treeOperator.calculateAABBFromMortonNumber(2);
	EXPECT_TRUE(bb2.isSame(expected2, tolerance));

	const Box3dd expected3(Vector3dd(0, 5, 0), Vector3dd(5, 10, 5));
	const auto bb3 = treeOperator.calculateAABBFromMortonNumber(3);
	EXPECT_TRUE(bb3.isSame(expected3, tolerance));
}

TEST(LinearOctreeTest, TestCalculateAABBFromIndices)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctreeOperator treeOperator;
	treeOperator.init(space, 2);

	const Box3dd expected1(Vector3dd(0, 0, 0), Vector3dd(2.5, 2.5, 2.5));
	const auto bb1 = treeOperator.calculateAABBFromIndices({ 0,0,0 });
	EXPECT_TRUE(expected1.isSame(bb1, tolerance));

	const Box3dd expected2(Vector3dd(2.5, 0, 0), Vector3dd(5.0, 2.5, 2.5));
	const auto bb2 = treeOperator.calculateAABBFromIndices({ 1,0,0 });
	EXPECT_TRUE(expected2.isSame(bb2, tolerance));
}

TEST(LinearOctreeTest, TestMinBoxSize)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctreeOperator treeOperator;
	treeOperator.init(space, 2);
	const auto actual = treeOperator.getMinBoxSize();
	const Vector3dd expected(2.5, 2.5, 2.5);
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}

TEST(LinearOctreeTest, TestGetParentLevel)
{
	const Box3dd rootSpace(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(9, 3, 3));
	LinearOctreeOperator treeOperator;
	treeOperator.init(rootSpace, 2);
	EXPECT_EQ(0, treeOperator.getParentLevel(space));
}

TEST(LinearOctreeTest, TestAdd)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctreeOperator treeOperator;
	treeOperator.init(space, 2);
	IOctreeItem item(Triangle3d(Vector3dd(3, 3, 3), Vector3dd(6, 0, 0), Vector3dd(3, 6, 6)));
	treeOperator.add(&item);
	const auto items = treeOperator.findItems(Box3dd(Vector3dd(3, 3, 3), Vector3dd(6, 6, 6)));
	EXPECT_EQ(items.size(), 1);
}