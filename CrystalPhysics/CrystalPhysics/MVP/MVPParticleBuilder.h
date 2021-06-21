#pragma once

#include <vector>
#include "../../../Crystal/Shape/Volume.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;

class MVPParticleBuilder
{
public:
	MVPVolumeParticle* create(const Math::Vector3df& position, const float radius, const int unum, const int vnum, const int wnum, const float weight);

private:
};
	}
}