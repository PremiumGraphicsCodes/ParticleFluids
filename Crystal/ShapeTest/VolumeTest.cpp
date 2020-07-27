#include "pch.h"
#include "gtest/gtest.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	const auto tolerance = 1.0e-12;
}

TEST(VolumeTest, TestGetCellLength)
{
	Volume<double> volume(Box3d(Vector3dd(0,0,0), Vector3dd(2,2,2)));
	volume.build(2, 1, 4);
	const auto actual = volume.getCellLength();
	const auto expected = Vector3dd(1.0, 2.0, 0.5);
	EXPECT_TRUE(::areSame(expected, actual, ::tolerance));
}

TEST(VolumeTest, TestGetCellPosition)
{
	Volume<double> volume(Box3d(Vector3dd(0, 0, 0), Vector3dd(2, 2, 2)));
	volume.build(2, 1, 4);
	
	{
		const auto actual = volume.getCellPosition(0, 0, 0);
		const auto expected = Vector3dd(0.5, 1.0, 0.25);
		EXPECT_TRUE(::areSame(expected, actual, ::tolerance));
	}
	{
		const auto actual = volume.getCellPosition(1, 0, 0);
		const auto expected = Vector3dd(1.5, 1.0, 0.25);
		EXPECT_TRUE(::areSame(expected, actual, ::tolerance));
	}

}