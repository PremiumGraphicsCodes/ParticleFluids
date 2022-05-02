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


	void createStaticScene();

	void createEmitterScene();

	void addFluidScene(Physics::MVPFluidScene* scene) { this->fluidScenes.push_back(scene); }

	void clear();

	Physics::MVPFluidScene* staticScene;
	Physics::MVPFluidEmitterScene* emitterScene;
	Physics::CSGBoundaryScene* csgScene;
	Physics::MVPFluidSolver solver;
	Physics::MVPUpdater updator;
	SolverExporter* exporter;

private:
	Scene::World* world;
	std::vector<Physics::MVPFluidScene*> fluidScenes;

};
	}
}