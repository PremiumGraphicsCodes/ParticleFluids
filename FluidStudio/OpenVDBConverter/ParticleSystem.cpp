#include "ParticleSystem.h"

#include "ParticleSystemImpl.h"

using namespace Crystal::OpenVDB;


ParticleSystem::ParticleSystem() :
    impl(std::make_unique<ParticleSystemImpl>())
{}
