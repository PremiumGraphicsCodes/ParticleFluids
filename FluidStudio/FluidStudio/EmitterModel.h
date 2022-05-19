#pragma once

#include "CrystalScene/Scene/World.h"
#include "IModel.h"

namespace PG {
	namespace FS {

class EmitterModel : IModel
{
public:
	EmitterModel();

	void create(Crystal::Scene::World* world);

	void reset(Crystal::Scene::World* world);

	tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent) override;

	std::string name = "Emitter01";
	int fluidId;
	int particleSystemId;
	float pressureCoe;
	float viscosityCoe;
	float heatDiffuseCoe;
	float dragForceCoe;
	float dragHeatCoe;
	float temperature;
	int lifeLimit;
	Crystal::Math::Vector3df initialVelocity;
};

	}
}