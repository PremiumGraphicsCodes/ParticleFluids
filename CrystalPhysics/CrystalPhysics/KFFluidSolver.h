#pragma once

#include <vector>
#include <list>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Scene/IAnimator.h"

#include "../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "MeshBoundaryScene.h"

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;
		class KFFluidScene;
		class KFFluidEmitterScene;
		class CSGBoundaryScene;

class KFBoundarySolver
{
public:
	KFBoundarySolver() {}

	void addBoundaryScene(KFFluidScene* scene) { this->boundaries.push_back(scene); }

	void setup(const float effectLength);

	void clear() {
		boundaries.clear();
//		spaceHash.clear();
	}

	std::vector<Shape::IParticle*> findNeighbors(const Math::Vector3dd& position);

private:
	std::list<KFFluidScene*> boundaries;
	std::unique_ptr<Space::CompactSpaceHash3d> spaceHash;
};

class KFFluidSolver : public Scene::IAnimator
{
public:
	KFFluidSolver() {}

	explicit KFFluidSolver(const int id);

	void setupBoundaries();

	void clear();

	void addFluidScene(KFFluidScene* scene);

	void addBoundaryScene(KFFluidScene* scene);

	void addEmitterScene(KFFluidEmitterScene* scene);

	void addBoundary(CSGBoundaryScene* scene) { this->csgBoundaries.push_back(scene); }

	void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

	void setEffectLength(const float effectLength) { this->effectLength = effectLength; }

	void simulate();

	void step() override;

private:

	float calculateTimeStep(const std::vector<KFMacroParticle*>& particles);

	void solveBoundary(KFMacroParticle* particle, const double dt);
	//void solveBoundary(const std::vector<MacroParticle*>& particles);
	
	std::list<KFFluidScene*> fluids;
	std::list<KFFluidEmitterScene*> emitters;
	KFBoundarySolver boundarySolver;
	std::list<CSGBoundaryScene*> csgBoundaries;
	float effectLength = 2.0f;
	float maxTimeStep = 0.03f;
	int currentTimeStep = 0;
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