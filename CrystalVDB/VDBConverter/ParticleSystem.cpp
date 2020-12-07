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

void ParticleSystem::fromCrystal(const Crystal::Scene::ParticleSystemScene& scene)
{
    auto particleSystem = scene.getShape();

    const auto particles = scene.getShape()->getParticles();
    for (auto p : particles) {
        const auto position = p->getPosition();
        const auto size = static_cast<double>(p->getAttribute().size);
        this->add(p->getPosition(), size);
    }
}
