#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "ParticlesToVolumeConverter.h"
#include "ParticleSystem.h"
#include "ParticleSystemImpl.h"
#include "VolumeImpl.h"
#include "Volume.h"

using namespace openvdb;
using namespace Crystal::OpenVDB;

std::unique_ptr<Volume> ParticlesToVolumeConverter::toVolume(const ParticleSystem& particles)
{
    // Rasterize into an SDF.
    auto sdf = createLevelSet<FloatGrid>();
    auto p = particles.getImpl();
    tools::particlesToSdf(*p, *sdf/*radius=10.0*/);
    std::unique_ptr<VolumeImpl> vImpl = std::make_unique<VolumeImpl>(sdf);
    std::unique_ptr<Volume> v = std::make_unique<Volume>(std::move(vImpl) );
    return std::move(v);
}