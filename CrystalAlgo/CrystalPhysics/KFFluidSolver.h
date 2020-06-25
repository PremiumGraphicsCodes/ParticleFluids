#pragma once

#include <vector>
#include <list>
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

#include "MicroParticle.h"
#include "MacroParticle.h"

#include "../../Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class FluidScene;

class KFFluidSolver : public Scene::IAnimator
{
public:
	KFFluidSolver();

	void add(FluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate(const double dt);

	void step() override;

	//void addBoundary()

private:
	std::list<FluidScene*> fluids;
	double timeStep;
};

		}
	}
}