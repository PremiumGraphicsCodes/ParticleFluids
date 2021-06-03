#include "SPHFlameParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

SPHFlameParticle::SPHFlameParticle(const Vector3df& center, const float radius, SPHConstant* constant) :
	CSPHParticle(center, radius, constant)
{}
