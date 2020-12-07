#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

#include <memory>

namespace Crystal {
    namespace Shape {
        class IParticleSystem;
    }
    namespace VDB {
        class ParticleSystemImpl;

class ParticleSystem : private UnCopyable
{
public:
    ParticleSystem();

    ~ParticleSystem();

    void add(const Math::Vector3dd& position, const double radius);

    void fromCrystal(const Crystal::Shape::IParticleSystem& ps);

    Math::Vector3dd getPosition(const int index) const;

 //   Crystal::Scene::ParticleSystemScene* toCrystal() const;

    const ParticleSystemImpl* getImpl() const { return impl; }

private:
    ParticleSystemImpl* impl;
};

    }
}