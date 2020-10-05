#pragma once

#include <memory>

namespace Crystal {
    namespace OpenVDB {
        class ParticleSystemImpl;

class ParticleSystem
{
public:
    ParticleSystem();

    ~ParticleSystem() {};

    const ParticleSystemImpl* getImpl() const { return impl.get(); }

private:
    std::unique_ptr<ParticleSystemImpl> impl;
};

    }
}