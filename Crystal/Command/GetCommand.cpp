#include "GetCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


GetCommand::GetCommand(const std::string& name)
{
}

std::any GetCommand::Get(World* world)
{
	if (name == "SceneList") {
		world->getObjects()->getRoot()->getChildren();
	}
	return std::any(0);
}
