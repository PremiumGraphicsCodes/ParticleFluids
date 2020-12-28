#include "VDBParticleSystem.h"

#include "VDBParticleSystemImpl.h"

#include "Converter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

Crystal::VDB::VDBParticleSystem::VDBParticleSystem(const int id, const std::string name) :
    IShapeScene(id, name)
{
    this->impl = std::make_unique<VDBParticleSystemImpl>();
    this->presenter = std::make_unique<VDBParticleSystemPresenter>(this);
}

VDBParticleSystem::~VDBParticleSystem()
{
}

void VDBParticleSystem::add(const Vector3dd& position, const double radius)
{
    const auto pp = Converter::toVDB(position);
    impl->add(pp, radius);
}

Crystal::Math::Vector3dd VDBParticleSystem::getPosition(const int index) const
{
    openvdb::Vec3R v;
    impl->getPos(index, v);
    return Converter::fromVDB(v);
}

float VDBParticleSystem::getSize(const int index) const
{
    openvdb::Real radius;
    openvdb::Vec3R v;
    impl->getPosRad(index, v, radius);
    return radius;
}

void VDBParticleSystem::fromCrystal(const std::vector<Vector3dd>& positions, const float radius)
{
    for (const auto& p : positions) {
        this->add(p, radius);
    }
}

Box3d VDBParticleSystem::getBoundingBox() const
{
    Box3d box(getPosition(0));
    const auto size = impl->size();
    for (int i = 0; i < size; ++i) {
        box.add(getPosition(i));
    }
    return box;
}