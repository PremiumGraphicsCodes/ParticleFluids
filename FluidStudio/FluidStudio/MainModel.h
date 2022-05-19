#pragma once

#include "SolverModel.h"
#include "IModel.h"

namespace PG {
	namespace FS {

class MainModel : public IModel
{
public:
	MainModel(Crystal::Scene::World* world) : world(world)
	{}

	void init();

	SolverModel* getSolver() { return &solverModel; }

	tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent) override;

	bool fromXML(tinyxml2::XMLElement* parent) override;

private:
	Crystal::Scene::World* world;
	SolverModel solverModel;
};
	}
}