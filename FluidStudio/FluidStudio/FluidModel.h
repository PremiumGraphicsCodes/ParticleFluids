#pragma once

#include "CrystalScene/Scene/World.h"

#include "IModel.h"

namespace PG {
	namespace FS {

class FluidModel : public IModel
{
public:
	void create(Crystal::Scene::World* world);

	void reset(Crystal::Scene::World* world);

	tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent) override;

	bool fromXML(tinyxml2::XMLElement* parent);

	std::string name = "Fluid01";
	int fluidId;
	int particleSystemId;
	float pressureCoe;
	float viscosityCoe;
	float heatDiffuseCoe;
	float dragForceCoe;
	float dragHeatCoe;
};
	}
}