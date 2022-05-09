#pragma once

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "FluidModel.h"
#include "EmitterModel.h"

#include "SolverExporter.h"

namespace Crystal {
	namespace UI {

class SolverModel
{
public:
	void init(Scene::World* world);

	void reset(Scene::World* world);

	SolverExporter* getExporter() { return exporter; }

	Physics::CSGBoundaryScene* getBoundary() { return csgScene; }

	Physics::MVPFluidSolver* getSolver() { return &solver; }

	const std::vector<std::unique_ptr<FluidModel>>& getFluids() const { return fluids; }
	
	const std::vector<std::unique_ptr<EmitterModel>>& getEmitters() const { return emitters; }

	void addFluid(Scene::World* world);

	void addEmitter(Scene::World* world);

private:
	std::vector<std::unique_ptr<FluidModel>> fluids;
	std::vector<std::unique_ptr<EmitterModel>> emitters;
	SolverExporter* exporter;
	Physics::MVPUpdater updator;
	Physics::CSGBoundaryScene* csgScene;
	Physics::MVPFluidSolver solver;

};

	}
}