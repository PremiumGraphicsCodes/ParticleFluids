#include "VDBParticleSystem.h"

#include "ParticleSystemImpl.h"

#include "Converter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

Crystal::VDB::VDBParticleSystem::VDBParticleSystem(const int id, const std::string name) :
    IShapeScene(id, name),
    impl(new ParticleSystemImpl())
{
}

VDBParticleSystem::~VDBParticleSystem()
{
    delete impl;
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

std::unique_ptr<Crystal::Shape::IParticleSystem> VDBParticleSystem::toCrystal() const
{
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