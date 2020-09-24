#pragma once

#include <vector>
#include <list>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;
		class KFFluidScene;

class KFFluidSolver : public Scene::IAnimator
{
public:
	struct Args
	{
		std::list<KFFluidScene*> fluids;
		std::list<KFFluidScene*> boundaries;
		std::list<Math::Box3d> surfaces;
		double maxTimeStep = 0.03;
	};

	KFFluidSolver();

	void setArgs(const Args& args) { this->args = args; }

	void simulate();

	void step() override;

private:
	double calculateTimeStep(const std::vector<KFMacroParticle*>& particles);

	void solveBoundary(KFMacroParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
	Args args;
};

	}
}