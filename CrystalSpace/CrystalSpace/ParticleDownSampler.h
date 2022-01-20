#pragma once

#include <vector>
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Space {

class ParticleDownSampler
{
public:
	static std::vector<Math::Vector3dd> downSample(const std::vector<Shape::IParticle*>& particles, const float leafSize);

private:
};
	}
}