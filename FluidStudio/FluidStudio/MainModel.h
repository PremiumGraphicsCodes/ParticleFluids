#pragma once

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"

#include "SolverExporter.h"

namespace Crystal {
	namespace UI {

class MainModel
{
public:
	MainModel(Scene::World* world) : world(world)
	{}

	void init();

	void addFluidScene(Physics::MVPFluidScene* scene) {
		this->fluidScenes.push_back(scene);
	}
	
	void addStaticScene(Physics::MVPFluidScene* scene) { this->staticScenes.push_back(scene); }

	void addEmitterScene(Physics::MVPFluidEmitterScene* scene) { this->emitterScenes.push_back(scene); }

	void clear();

	void resetSolver();

	Physics::CSGBoundaryScene* csgScene;
	Physics::MVPFluidSolver solver;
	Physics::MVPUpdater updator;
	SolverExporter* exporter;

private:
	Scene::World* world;
	std::vector<Physics::MVPFluidScene*> fluidScenes;
	std::vector<Physics::MVPFluidScene*> staticScenes;
	std::vector<Physics::MVPFluidEmitterScene*> emitterScenes;

};
	}
}