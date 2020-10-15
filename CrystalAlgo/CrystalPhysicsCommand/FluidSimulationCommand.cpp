#include "FluidSimulationCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;

FluidSimulationCommand::Args::Args() :
	fluidSceneId("fluidSceneId", 0),
	timeStep("timeStep", 0.03f)
{
	add(&fluidSceneId);
	add(&timeStep);
}

std::string FluidSimulationCommand::getName()
{
	return "FluidSimulation";
}

bool FluidSimulationCommand::execute(World* world)
{
	return false;
}
