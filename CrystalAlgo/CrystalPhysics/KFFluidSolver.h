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

	KFFluidSolver();

	void clear() {
		fluids.clear();
		boundaries.clear();
		surfaces.clear();
		maxTimeStep = 0.03f;
	}

	void addFluidScene(KFFluidScene* scene) { this->fluids.push_back(scene); }

	void addBoundaryScene(KFFluidScene* scene) { this->boundaries.push_back(scene); }

	void addSurface(const Math::Box3d& surface) { this->surfaces.push_back(surface); }

	void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

	void simulate();

	void step() override;

private:
	float calculateTimeStep(const std::vector<KFMacroParticle*>& particles);

	void solveBoundary(KFMacroParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
	
	std::list<KFFluidScene*> fluids;
	std::list<KFFluidScene*> boundaries;
	std::list<Math::Box3d> surfaces;
	float maxTimeStep = 0.03f;
};

	}
}