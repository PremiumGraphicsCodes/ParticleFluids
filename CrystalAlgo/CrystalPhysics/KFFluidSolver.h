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
		class CSGBoundaryScene;

class KFFluidSolver : public Scene::IAnimator
{
public:
	KFFluidSolver() {}

	explicit KFFluidSolver(const int id);

	void clear() {
		fluids.clear();
		boundaries.clear();
		csgBoundaries.clear();
		maxTimeStep = 0.03f;
	}

	void addFluidScene(KFFluidScene* scene) { this->fluids.push_back(scene); }

	void addBoundaryScene(KFFluidScene* scene) { this->boundaries.push_back(scene); }

	void addBoundary(CSGBoundaryScene* scene) { this->csgBoundaries.push_back(scene); }

	void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

	void simulate();

	void step() override;

private:
	float calculateTimeStep(const std::vector<KFMacroParticle*>& particles);

	void solveBoundary(KFMacroParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
	
	std::list<KFFluidScene*> fluids;
	std::list<KFFluidScene*> boundaries;
	std::list<CSGBoundaryScene*> csgBoundaries;
	float maxTimeStep = 0.03f;
};

class KFFUpdater : public Scene::IAnimator
{
public:
	KFFUpdater() {}

	void add(Physics::KFFluidScene* f) { fluids.push_back(f); }

	void step() override;

private:
	std::list<Physics::KFFluidScene*> fluids;
};


	}
}