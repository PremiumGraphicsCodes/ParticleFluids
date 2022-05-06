#pragma once

#include "CrystalScene/Scene/World.h"

namespace Crystal {
	namespace UI {

class EmitterModel
{
public:
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
};

	}
}