#include "gtest/gtest.h"

#include "../VDBConverter/MeshToVolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

// from https://github.com/AcademySoftwareFoundation/openvdb/blob/master/openvdb/openvdb/unittest/TestMeshToVolume.cc
TEST(MeshToVolumeTest, TestToVolume)
{
    VDBPolygonMesh mesh;

    // cube vertices
    mesh.addVertex(Vector3dd( 2, 2, 2)); // 0       6--------7
    mesh.addVertex(Vector3dd( 5, 2, 2)); // 1      /|       /|
    mesh.addVertex(Vector3dd( 2, 5, 2)); // 2     2--------3 |
    mesh.addVertex(Vector3dd( 5, 5, 2)); // 3     | |      | |
    mesh.addVertex(Vector3dd( 2, 2, 5)); // 4     | 4------|-5
    mesh.addVertex(Vector3dd( 5, 2, 5)); // 5     |/       |/
    mesh.addVertex(Vector3dd( 2, 5, 5)); // 6     0--------1
    mesh.addVertex(Vector3dd( 5, 5, 5)); // 7

    // cube faces
    mesh.addQuad({ 0, 1, 3, 2 }); // front
    mesh.addQuad({ 5, 4, 6, 7 }); // back
    mesh.addQuad({ 0, 2, 6, 4 }); // left
    mesh.addQuad({ 1, 5, 7, 3 }); // right
    mesh.addQuad({ 2, 3, 7, 6 }); // top
    mesh.addQuad({ 0, 4, 5, 1 }); // bottom

    Crystal::VDB::MeshToVolumeConverter converter;
    auto volume = converter.toVolume(mesh);
    //volume->

    /*
    math::Transform::Ptr xform = math::Transform::createLinearTransform();

    tools::QuadAndTriangleDataAdapter<Vec3s, Vec4I> mesh(points, quads);

    FloatGrid::Ptr grid = tools::meshToVolume<FloatGrid>(mesh, *xform);

    EXPECT_TRUE(grid.get() != NULL);
    EXPECT_EQ(int(GRID_LEVEL_SET), int(grid->getGridClass()));
    EXPECT_EQ(1, int(grid->baseTree().leafCount()));

    grid = tools::meshToLevelSet<FloatGrid>(*xform, points, quads);

    EXPECT_TRUE(grid.get() != NULL);
    EXPECT_EQ(int(GRID_LEVEL_SET), int(grid->getGridClass()));
    EXPECT_EQ(1, int(grid->baseTree().leafCount()));
    */
}