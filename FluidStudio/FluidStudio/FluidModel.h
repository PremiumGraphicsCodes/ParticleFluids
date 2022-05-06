#pragma once

#include "CrystalScene/Scene/World.h"

namespace Crystal {
	namespace UI {


class FluidModel
{
public:
	void create(Scene::World* world);

	void reset(Scene::World* world);

	int getFluidId() const { return fluidId; }

	int getParticleSystemId() const { return particleSystemId; }

private:
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