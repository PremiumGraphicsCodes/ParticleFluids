#pragma once

#include "CrystalScene/Scene/World.h"

namespace PG {
	namespace FS {

class FluidModel
{
public:
	void create(Crystal::Scene::World* world);

	void reset(Crystal::Scene::World* world);

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