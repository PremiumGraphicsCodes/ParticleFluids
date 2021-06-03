#pragma once

#include "CSPHParticle.h"

namespace Crystal {
	namespace Physics {

class SPHFlameParticle : public CSPHParticle
{
public:
	SPHFlameParticle(const Math::Vector3df& center, const float radius, SPHConstant* constant);

private:
};

	}
}