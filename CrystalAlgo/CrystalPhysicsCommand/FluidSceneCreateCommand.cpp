#include "FluidSceneCreateCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneCreateCommand::getName()
{
	return "FluidSceneCreateCommand";
}

FluidSceneCreateCommand::Args::Args() :
	particleSystemId("ParticleSystemId", -1)
{
	add(&particleSystemId);
}

FluidSceneCreateCommand::Results::Results() :
	newId("newId", 0)
{
	add(&newId);
}

FluidSceneCreateCommand::FluidSceneCreateCommand() :
	ICommand(&args, &results)
{}

bool FluidSceneCreateCommand::execute(World* world)
{
	return false;
}

