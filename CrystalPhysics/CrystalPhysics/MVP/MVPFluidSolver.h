#pragma once

#include <vector>
#include <list>

#include "../../../Crystal/Math/Vector3d.h"
#include "../../../Crystal/Math/Box3d.h"
#include "../../../Crystal/Shape/IParticle.h"
#include "../../../Crystal/Scene/IAnimator.h"

#include "../../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "../MeshBoundaryScene.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;
		class MVPFluidScene;
		class KFFluidEmitterScene;
		class IKFFluidScene;
		class CSGBoundaryScene;

class MVPBoundarySolver
{
public:
	MVPBoundarySolver() {}

	void addBoundaryScene(MVPFluidScene* scene) { this->boundaries.push_back(scene); }

	void setup(const float effectLength);

	void clear() {
		boundaries.clear();
//		spaceHash.clear();
	}

	std::vector<Shape::IParticle*> findNeighbors(const Math::Vector3dd& position);

private:
	std::list<MVPFluidScene*> boundaries;
	std::unique_ptr<Space::CompactSpaceHash3d> spaceHash;
};

class MVPFluidSolver : public Scene::IAnimator
{
public:
	MVPFluidSolver() {}

	explicit MVPFluidSolver(const int id);

	void setupBoundaries();

	void clear();

	void addFluidScene(MVPFluidScene* scene);

	void addBoundaryScene(MVPFluidScene* scene);

	void addEmitterScene(KFFluidEmitterScene* scene);

	void addBoundary(CSGBoundaryScene* scene) { this->csgBoundaries.push_back(scene); }

	void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

	void setEffectLength(const float effectLength) { this->effectLength = effectLength; }

	void simulate();

	void step() override;

private:

	float calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles);

	void solveBoundary(MVPVolumeParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
	
	std::list<MVPFluidScene*> fluids;
	std::list<KFFluidEmitterScene*> emitters;
	MVPBoundarySolver boundarySolver;
	std::list<CSGBoundaryScene*> csgBoundaries;
	float effectLength = 2.0f;
	float maxTimeStep = 0.03f;
	int currentTimeStep = 0;
};

class MVPUpdater : public Scene::IAnimator
{
public:
	MVPUpdater() {}

	void add(Physics::IKFFluidScene* f) { fluids.push_back(f); }

	void step() override;

private:
	std::list<Physics::IKFFluidScene*> fluids;
};


	}
}