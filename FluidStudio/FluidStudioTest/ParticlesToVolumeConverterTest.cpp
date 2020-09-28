#include "pch.h"


#include "../FluidStudio/ParticlesToVolumeConverter.h"

using namespace Crystal::OpenVDB;

TEST(ParticlesToVolumeConverterTest, TestConvert)
{
    /*
    {
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
    }
    */
    {
        ParticleSystem particles;
        particles.add(openvdb::v7_1::Vec3R(1, 2, 3), 2.0);
        ParticlesToVolumeConverter pToVolume;
        auto volume = pToVolume.toVolume(particles);

        /*
        openvdb::io::File file("Test1Volume.vdb");
        file.write({ volume });
        file.close();

        VolumeToMeshConverter vToMesh;
        auto mesh = vToMesh.toMesh(*volume);

        OBJFileWriter writer;
        writer.write("TestMesh.obj", mesh);
        */
    }
}