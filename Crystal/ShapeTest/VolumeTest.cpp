#include "pch.h"
#include "gtest/gtest.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Shape;

TEST(VolumeTest, TestBuild)
{
	Volume<double> volume;
	volume.build(2, 2, 2);
}