#pragma once

#include <vector>
#include <list>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IPoint.h"
#include "../../Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {
		class MacroParticle;
		class KFFluidScene;

class KFFluidSolver : public Scene::IAnimator
{
public:
	KFFluidSolver();

	void add(KFFluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate();

	void step() override;

	void setBoundary(const Math::Box3d& boundary) { this->boundary = boundary; }

	void setTimeStep(const double dt) { this->dt = dt; }

private:
	std::list<KFFluidScene*> fluids;
	Math::Box3d boundary;
	double dt;

private:
	void solveBoundary(MacroParticle* particle);
};

	}
}