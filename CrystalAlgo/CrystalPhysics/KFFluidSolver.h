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

	void add(KFFluidScene* fluid) { this->fluids.push_back(fluid); }

	void addBoundary(KFFluidScene* boundary) { this->boundaries.push_back(boundary); }

	void simulate();

	void step() override;

	void setBoundary(const Math::Box3d& surface) {
		this->surfaces.clear();
		this->surfaces.push_back(surface); }

	void setTimeStep(const double dt) { this->maxTimeStep = dt; }

private:
	std::list<KFFluidScene*> fluids;
	std::list<KFFluidScene*> boundaries;
	std::list<Math::Box3d> surfaces;
	double maxTimeStep;

private:
	double calculateTimeStep(const std::vector<KFMacroParticle*>& particles);

	void solveBoundary(KFMacroParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
};

	}
}