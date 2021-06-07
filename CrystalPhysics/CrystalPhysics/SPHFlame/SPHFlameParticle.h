#pragma once

#include "../CSPHParticle.h"

namespace Crystal {
	namespace Physics {

struct SPHFlameConstant
{
	float k_hd;
	float k_fd;
	float k_rs;
};

class SPHFlameParticle : public CSPHParticle
{
public:
	SPHFlameParticle(const Math::Vector3df& center, const float radius, SPHConstant* constant, SPHFlameConstant* flameConstant);

	void solveHeatDiffuse(const SPHFlameParticle& rhs);

	void solveFuelDiffuse(const SPHFlameParticle& rhs);

	float getReactionSpeed();

private:
	float temperature;
	float fuel;
	SPHFlameConstant* flameConstant;
};

	}
}