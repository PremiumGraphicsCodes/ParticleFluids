#pragma once

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "FluidModel.h"

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

private:

	std::vector<std::unique_ptr<FluidModel>> fluids;
	std::vector<Physics::MVPFluidEmitterScene*> emitterScenes;
	SolverExporter* exporter;
	Physics::MVPUpdater updator;
	Physics::CSGBoundaryScene* csgScene;
	Physics::MVPFluidSolver solver;

};

	}
}