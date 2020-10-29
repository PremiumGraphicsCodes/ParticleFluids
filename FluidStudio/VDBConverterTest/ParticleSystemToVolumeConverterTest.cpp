#include "gtest/gtest.h"
#include "../OpenVDBConverter/ParticleSystemToVolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

TEST(ParticleSystemToVolumeConverterTest, TestToVolume)
{
    ParticleSystem ps;
    ps.add(Vector3dd(0, 0, 0), 10.0);

    ParticleSystemToVolumeConverter pToVolume;
    auto volume = pToVolume.toVolume(ps);
}