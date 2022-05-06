#pragma once

#include "SolverModel.h"

namespace Crystal {
	namespace UI {

class MainModel
{
public:
	MainModel(Scene::World* world) : world(world)
	{}

	void init();

	SolverModel* getSolver() { return &solverModel; }
	
private:
	Scene::World* world;
	SolverModel solverModel;
};
	}
}