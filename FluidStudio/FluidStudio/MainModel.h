#pragma once

#include "SolverModel.h"

namespace PG {
	namespace FS {

class MainModel
{
public:
	MainModel(Crystal::Scene::World* world) : world(world)
	{}

	void init();

	SolverModel* getSolver() { return &solverModel; }
	
private:
	Crystal::Scene::World* world;
	SolverModel solverModel;
};
	}
}