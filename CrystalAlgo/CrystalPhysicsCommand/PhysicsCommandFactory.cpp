#include "PhysicsCommandFactory.h"

#include "FluidSceneCreateCommand.h"
#include "FluidSceneUpdateCommand.h"
#include "FluidSimulationCommand.h"
#include "CSGBoundarySceneCreateCommand.h"
#include "CSGBoundarySceneUpdateCommand.h"

using namespace Crystal::Command;
using namespace Crystal::Physics;

std::unique_ptr<ICommand> PhysicsCommandFactory::create(const std::string& name)
{
	if (name == FluidSceneCreateCommand::getName()) {
		return std::make_unique<FluidSceneCreateCommand>();
	}
	else if (name == FluidSceneUpdateCommand::getName()) {
		return std::make_unique<FluidSceneUpdateCommand>();
	}
	else if (name == FluidSimulationCommand::getName()) {
		return std::make_unique<FluidSimulationCommand>();
	}
	else if (name == CSGBoundarySceneCreateCommand::getName()) {
		return std::make_unique<CSGBoundarySceneCreateCommand>();
	}
	else if (name == CSGBoundarySceneUpdateCommand::getName()) {
		return std::make_unique<CSGBoundarySceneUpdateCommand>();
	}
	return nullptr;
}
