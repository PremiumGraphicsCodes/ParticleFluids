#include "gtest/gtest.h"
#include "../OpenVDBConverter/VolumeToMeshConverter.h"

using namespace Crystal::OpenVDB;

TEST(VolumeToMeshConverterTest, Test)
{
    Volume grid(1.0f);
    grid.fill(1, 6, -1.0f);

    VolumeToMeshConverter vToMesh;
    const auto mesh = vToMesh.toMesh(grid);
    EXPECT_FALSE( mesh->getVertices().empty() );
    //mesh->get
    //assert(!mesh.points.empty());
    //assert(size_t(216) == mesh.quads.size());
}
