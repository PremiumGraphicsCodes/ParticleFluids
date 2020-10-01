#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "ParticlesToVolumeConverter.h"
#include "ParticleSystem.h"

using namespace openvdb;
using namespace Crystal::OpenVDB;

openvdb::FloatGrid::Ptr ParticlesToVolumeConverter::toVolume(const ParticleSystem& particles)
{
    // Rasterize into an SDF.
    auto sdf = createLevelSet<FloatGrid>();
    tools::particlesToSdf(particles, *sdf/*radius=10.0*/);

    return std::move(sdf);
}