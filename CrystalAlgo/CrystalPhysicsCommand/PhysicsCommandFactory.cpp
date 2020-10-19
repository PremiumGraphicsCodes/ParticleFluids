#include "PhysicsCommandFactory.h"

#include "FluidSceneCreateCommand.h"

using namespace Crystal::Command;
using namespace Crystal::Physics;

std::unique_ptr<ICommand> PhysicsCommandFactory::create(const std::string& name)
{
	return std::make_unique<FluidSceneCreateCommand>();
}
