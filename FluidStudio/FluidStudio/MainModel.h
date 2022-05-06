#pragma once

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "FluidModel.h"

#include "SolverExporter.h"

namespace Crystal {
	namespace UI {

class MainModel
{
public:
	MainModel(Scene::World* world) : world(world)
	{}

	void init();
	
	void addStaticScene(Physics::MVPFluidScene* scene) { this->staticScenes.push_back(scene); }

	void addEmitterScene(Physics::MVPFluidEmitterScene* scene) { this->emitterScenes.push_back(scene); }

	void clear();

	void resetSolver();

	SolverExporter* getExporter() { return exporter; }

	Physics::CSGBoundaryScene* getBoundary() { return csgScene; }

	Physics::MVPFluidSolver* getSolver() { return &solver; }

private:
	Scene::World* world;
	std::vector<std::unique_ptr<FluidModel>> fluids;
	std::vector<Physics::MVPFluidScene*> staticScenes;
	std::vector<Physics::MVPFluidEmitterScene*> emitterScenes;
	SolverExporter* exporter;
	Physics::MVPUpdater updator;
	Physics::CSGBoundaryScene* csgScene;
	Physics::MVPFluidSolver solver;

};
	}
}