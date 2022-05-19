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

	Crystal::UI::SolverModel* getSolver() { return &solverModel; }
	
private:
	Crystal::Scene::World* world;
	Crystal::UI::SolverModel solverModel;
};
	}
}