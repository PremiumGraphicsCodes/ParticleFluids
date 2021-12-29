#include "openvdb/openvdb.h"
#include "openvdb/tools/ParticlesToLevelSet.h"
#include <openvdb/tools/LevelSetUtil.h>

#include "VDBParticleSystemConverter.h"
#include "VDBParticleSystemScene.h"
#include "VDBParticleSystemImpl.h"
#include "VDBVolumeImpl.h"
#include "VDBVolumeScene.h"
#include "../../CrystalScene/Scene/ParticleSystemScene.h"

#include "Converter.h"

using namespace openvdb;
using namespace Crystal::Shape;
using namespace Crystal::VDB;
using namespace Crystal::Scene;

void VDBParticleSystemConverter::toVolume(const VDBParticleSystemScene& particles, const float radius, VDBVolumeScene* volume)
{
    // Rasterize into an SDF.
    auto sdf = createLevelSet<FloatGrid>();
    sdf->setName("density");
    auto p = particles.getImpl();
    if (p->size() == 0) {
        return;
    }
    tools::particlesToSdf(*p, *sdf, radius);
    std::unique_ptr<VDBVolumeScene> v = std::make_unique<VDBVolumeScene>();
    volume->getImpl()->setPtr(sdf);
}

void VDBParticleSystemConverter::fromVDB(const VDBParticleSystemScene& src, ParticleSystemScene* ps)
{
    ps->clear();

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

void VDBParticleSystemConverter::toVDB(const IParticleSystemScene& src, VDBParticleSystemScene* dest)
{
    dest->clear();
    const auto positions = src.getPositions();
    for (const auto& p : positions) {
        dest->add(p, 1.0);
    }
}
