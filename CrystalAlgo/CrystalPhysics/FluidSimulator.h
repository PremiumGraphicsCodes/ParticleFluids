#pragma once

#include <vector>
#include <list>
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

#include "MicroParticle.h"
#include "MacroParticle.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class FluidScene;

class FluidSimulator
{
public:
	void add(FluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate(const double dt);

private:
	std::list<FluidScene*> fluids;
};

		}
	}
}