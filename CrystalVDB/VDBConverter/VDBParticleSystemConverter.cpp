#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "VDBParticleSystemConverter.h"
#include "VDBParticleSystem.h"
#include "VDBParticleSystemImpl.h"
#include "VolumeImpl.h"
#include "VDBVolume.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Converter.h"

using namespace openvdb;
using namespace Crystal::Shape;
using namespace Crystal::VDB;
using namespace Crystal::Scene;

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

void VDBParticleSystemConverter::fromVDB(const VDBParticleSystem& src, ParticleSystemScene* ps)
{
    auto impl = src.getImpl();
    const auto count = impl->size();
    for (int i = 0; i < count; ++i) {
        openvdb::Real radius;
        openvdb::Vec3R v;
        impl->getPosRad(i, v, radius);
        const auto p = Converter::fromVDB(v);
        ParticleAttribute attr;
        attr.color = Crystal::Graphics::ColorRGBAf(0, 0, 0, 0);
        attr.size = radius;
        ps->getShape()->add(p, attr);
    }
}

/*
VDBParticleSystem VDBParticleSystemConverter::toVDB(const Shape::IParticleSystem& src)
{
    src.getIParticles();
}
*/