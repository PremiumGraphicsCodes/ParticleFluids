#include "gtest/gtest.h"

#include "../OpenVDBConverter/OpenVDBFileWriter.h"
#include "../OpenVDBConverter/OpenVDBFileReader.h"
/*
#include "OpenVDBFileWriter.h"
#include "VolumeToMeshConverter.h"
#include "ParticlesToVolumeConverter.h"
#include "OBJFileWriter.h"

#include "ParticleSystem.h"
*/

using namespace openvdb;
using namespace Crystal::OpenVDB;


TEST(TestOpenVDBFileWriter, TestWrite)
{
    openvdb::initialize();
    OpenVDBFileWriter writer;
    writer.addPoint(openvdb::Vec3R(0, 1, 0));
    writer.addPoint(openvdb::Vec3R(1.5, 3.5, 1));
    writer.addPoint(openvdb::Vec3R(-1, 6, -2));
    writer.addPoint(openvdb::Vec3R(1.1, 1.25, 0.06));

    writer.setName("Points");
    writer.write("testWrite.vdb");
}

TEST(TestOpenVDBFileReader, TestRead)
{
    OpenVDBFileReader reader;
    reader.read("testWrite.vdb");
    const auto positions = reader.getPositions();
    EXPECT_EQ(4, positions.size());
}

/*
Crystal::OpenVDB::FSPSFileReader reader;
reader.read("C:\\Users\\PremiumGraphics\\Desktop\\1.fsps");
const auto positions = reader.getPositions();
Crystal::OpenVDB::OpenVDBFileWriter writer;
ParticleSystem particles;
for (const auto& p : positions) {
    writer.addPoint(p);
    particles.add(p, 2.0);
}
writer.write("Test1.vdb");

{
    ParticlesToVolumeConverter pToVolume;
    auto volume = pToVolume.toVolume(particles);

    openvdb::io::File file("Test1Volume.vdb");
    file.write({ volume });
    file.close();

    VolumeToMeshConverter vToMesh;
    auto mesh = vToMesh.toMesh(*volume);

    OBJFileWriter writer;
    writer.write("TestMesh.obj", mesh);
}
*/

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

