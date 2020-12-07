#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

#include <memory>

namespace Crystal {
    namespace Scene {
        class ParticleSystemScene;
    }
    namespace VDB {
        class ParticleSystemImpl;

class ParticleSystem : private UnCopyable
{
public:
    ParticleSystem();

    ~ParticleSystem();

    void add(const Math::Vector3dd& position, const double radius);

    void fromCrystal(const Crystal::Scene::ParticleSystemScene& scene);

    const ParticleSystemImpl* getImpl() const { return impl; }

private:
    ParticleSystemImpl* impl;
};

    }
}