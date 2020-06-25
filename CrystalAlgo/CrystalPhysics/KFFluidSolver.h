#pragma once

#include <vector>
#include <list>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IPoint.h"
#include "../../Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;

class KFFluidSolver : public Scene::IAnimator
{
public:
	KFFluidSolver();

	void add(KFFluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate(const double dt);

	void step() override;

	void setBoundary(const Math::Box3d& boundary) { this->boundary = boundary; }

private:
	std::list<KFFluidScene*> fluids;
	Math::Box3d boundary;
	double timeStep;
};

	}
}