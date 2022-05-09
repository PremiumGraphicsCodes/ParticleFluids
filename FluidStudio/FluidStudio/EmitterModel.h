#pragma once

#include "CrystalScene/Scene/World.h"

namespace Crystal {
	namespace UI {

class EmitterModel
{
public:
	EmitterModel();

	void create(Scene::World* world);

	void reset(Scene::World* world);

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
	Math::Vector3df initialVelocity;
};

	}
}