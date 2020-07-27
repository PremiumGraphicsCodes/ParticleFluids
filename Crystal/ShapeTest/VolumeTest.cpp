#include "pch.h"
#include "gtest/gtest.h"

#include "../../Crystal/Shape/Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

TEST(VolumeTest, TestBuild)
{
	Volume<double> volume(Box3d(Vector3dd(0,0,0), Vector3dd(1,1,1)));
	volume.build(2, 2, 2);
}