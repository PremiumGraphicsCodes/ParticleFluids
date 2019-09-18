#pragma once

#include "../Shape/IShape.h"

#include "Particle.h"

namespace Crystal {
	namespace Shape {

class IParticleSystem : public IShape
{
public:
	IParticleSystem() {}

	virtual ~IParticleSystem() {}

	virtual std::vector<IParticle*> getIParticles() const = 0;

private:
};

	}
}
