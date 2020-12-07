#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "ParticleSystemToVolumeConverter.h"
#include "VDBParticleSystem.h"
#include "ParticleSystemImpl.h"
#include "VolumeImpl.h"
#include "VDBVolume.h"

using namespace openvdb;
using namespace Crystal::VDB;

std::unique_ptr<VDBVolume> ParticleSystemToVolumeConverter::toVolume(const VDBParticleSystem& particles)
{
    // Rasterize into an SDF.
    auto sdf = createLevelSet<FloatGrid>();
    auto p = particles.getImpl();
    tools::particlesToSdf(*p, *sdf/*radius=10.0*/);
    std::unique_ptr<VDBVolume> v = std::make_unique<VDBVolume>();
    v->getImpl()->setPtr(sdf);
    return std::move(v);
}