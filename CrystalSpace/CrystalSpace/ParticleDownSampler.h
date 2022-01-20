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
	static Math::Box3dd calculateBox(const std::vector<Shape::IParticle*>& particles, const float cellLength);

	static std::vector<Math::Vector3df> downSample(const std::vector<Shape::IParticle*>& particles, const float leafSize, const Math::Box3df& bb);

private:
};
	}
}