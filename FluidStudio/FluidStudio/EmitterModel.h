#pragma once

#include "CrystalScene/Scene/World.h"

namespace PG {
	namespace FS {

class EmitterModel
{
public:
	EmitterModel();

	void create(Crystal::Scene::World* world);

	void reset(Crystal::Scene::World* world);

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