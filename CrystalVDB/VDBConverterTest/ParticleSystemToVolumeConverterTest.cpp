#include "gtest/gtest.h"
#include "../VDBConverter/ParticleSystemToVolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(ParticleSystemToVolumeConverterTest, TestToVolume)
{
    ParticleSystem ps;
    ps.add(Vector3dd(0, 0, 0), 10.0);

    ParticleSystemToVolumeConverter pToVolume;
    auto volume = pToVolume.toVolume(ps);
}