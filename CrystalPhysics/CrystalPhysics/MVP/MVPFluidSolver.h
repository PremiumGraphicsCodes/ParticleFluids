#pragma once

#include <vector>
#include <list>

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Box3d.h"
#include "Crystal/Shape/IParticle.h"
#include "CrystalScene/Scene/IAnimator.h"

#include "MVPBoundarySolver.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;
		class MVPFluidScene;
		class MVPFluidEmitterScene;
		class IMVPFluidScene;
		class CSGBoundaryScene;

class MVPFluidSolver : public Scene::IAnimator
{
public:
	MVPFluidSolver();

	explicit MVPFluidSolver(const int id);

	void setupBoundaries();

	void clear();

	void addFluidScene(MVPFluidScene* scene);

	void addBoundaryScene(MVPFluidScene* scene);

	void addEmitterScene(MVPFluidEmitterScene* scene);

	void addBoundary(CSGBoundaryScene* scene) { this->csgBoundaries.push_back(scene); }

	void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

	void setEffectLength(const float effectLength) { this->effectLength = effectLength; }

	void setExternalForce(const Math::Vector3df& externalForce) { this->externalForce = externalForce; }

	void simulate();

	void step() override;

private:

	float calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles);

	void solveBoundary(MVPVolumeParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
	
	std::list<MVPFluidScene*> fluids;
	std::list<MVPFluidEmitterScene*> emitters;
	MVPBoundarySolver boundarySolver;
	std::list<CSGBoundaryScene*> csgBoundaries;
	float effectLength = 2.0f;
	float maxTimeStep = 0.03f;
	int currentTimeStep = 0;
	Math::Vector3df externalForce;
};

class MVPUpdater : public Scene::IAnimator
{
public:
	MVPUpdater() {}

	void add(Physics::IMVPFluidScene* f) { fluids.push_back(f); }

	void step() override;

private:
	std::list<Physics::IMVPFluidScene*> fluids;
};


	}
}