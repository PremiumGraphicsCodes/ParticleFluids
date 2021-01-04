#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "VDBParticleSystemConverter.h"
#include "VDBParticleSystem.h"
#include "VDBParticleSystemImpl.h"
#include "VolumeImpl.h"
#include "VDBVolume.h"
#include "../../Crystal/Shape/ParticleSystem.h"

#include "Converter.h"

using namespace openvdb;
using namespace Crystal::Shape;
using namespace Crystal::VDB;

std::unique_ptr<VDBVolume> VDBParticleSystemConverter::toVolume(const VDBParticleSystem& particles, const float radius)
{
    // Rasterize into an SDF.
    auto sdf = createLevelSet<FloatGrid>();
    auto p = particles.getImpl();
    tools::particlesToSdf(*p, *sdf, radius);
    std::unique_ptr<VDBVolume> v = std::make_unique<VDBVolume>();
    v->getImpl()->setPtr(sdf);
    return std::move(v);
}

std::unique_ptr<IParticleSystem> VDBParticleSystemConverter::fromVDB(const VDBParticleSystem& src)
{
    auto impl = src.getImpl();
    const auto count = impl->size();
    auto shape = std::make_unique<Crystal::Shape::ParticleSystem<Crystal::Shape::IParticleAttribute>>();
    for (int i = 0; i < count; ++i) {
        openvdb::Real radius;
        openvdb::Vec3R v;
        impl->getPosRad(i, v, radius);
        const auto p = Converter::fromVDB(v);
        shape->add(p, Crystal::Shape::IParticleAttribute(radius));
    }
    return std::move(shape);
}

/*
VDBParticleSystem VDBParticleSystemConverter::toVDB(const Shape::IParticleSystem& src)
{
    src.getIParticles();
}
*/