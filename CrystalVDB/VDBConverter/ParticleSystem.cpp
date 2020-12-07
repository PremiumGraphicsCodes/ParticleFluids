#include "ParticleSystem.h"

#include "ParticleSystemImpl.h"

#include "Converter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;


ParticleSystem::ParticleSystem() :
    impl(new ParticleSystemImpl())
{}

ParticleSystem::~ParticleSystem()
{
    delete impl;
}

void ParticleSystem::add(const Vector3dd& position, const double radius)
{
    const auto pp = Converter::toVDB(position);
    impl->add(pp, radius);
}

Crystal::Math::Vector3dd ParticleSystem::getPosition(const int index) const
{
    openvdb::Vec3R v;
    impl->getPos(index, v);
    return Converter::fromVDB(v);
}

void ParticleSystem::fromCrystal(const Crystal::Shape::IParticleSystem& particleSystem)
{
    const auto particles = particleSystem.getIParticles();
    for (auto p : particles) {
        const auto position = p->getPosition();
        const auto size = static_cast<double>(p->getIAttribute()->size);
        this->add(p->getPosition(), size);
    }
}
