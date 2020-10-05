#include "ParticleSystem.h"

#include "ParticleSystemImpl.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;


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

