#include "gtest/gtest.h"
#include "../OpenVDBConverter/Volume.h"

//using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

TEST(VolumeTest, TestFill)
{
    /*
    using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
    using FloatGridType = openvdb::Grid<FloatTreeType>;

    FloatGridType grid(1.0f);
    openvdb::CoordBBox bbox(openvdb::Coord(1), openvdb::Coord(6));
    grid.tree().fill(bbox, -1.0f);
    */

	Volume volume(1.0f);
    volume.fill(1, 6, -1.0f);
}