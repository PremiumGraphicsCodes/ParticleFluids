#include "gtest/gtest.h"

#include "../OpenVDBConverter/OpenVDBFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

TEST(OpenVDBFileWriterTest, TestWrite)
{
    OpenVDBFileWriter writer;

    std::vector<Vector3dd> positions;
    positions.push_back(Vector3dd(0, 1, 0));
    positions.push_back(Vector3dd(1.5, 3.5, 1));
    positions.push_back(Vector3dd(-1, 6, -2));
    positions.push_back(Vector3dd(1.1, 1.25, 0.06));

    writer.open("testWrite.vdb");
    writer.write("points", positions);
}

/*
{
    using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
    using FloatGridType = openvdb::Grid<FloatTreeType>;

    FloatGridType grid(1.0f);
    openvdb::CoordBBox bbox(openvdb::Coord(1), openvdb::Coord(6));
    grid.tree().fill(bbox, -1.0f);

    VolumeToMeshConverter vToMesh;
    const auto mesh = vToMesh.toMesh(grid);
    assert(!mesh.points.empty());
    assert(size_t(216) == mesh.quads.size());
}
*/

