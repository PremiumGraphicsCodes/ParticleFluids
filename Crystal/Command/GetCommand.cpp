#include "GetCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


GetCommand::GetCommand(const std::string& name)
{
}

std::any GetCommand::Get(World* world)
{
	if (name == "SceneList") {
		const auto& children = world->getObjects()->getRoot()->getChildren();
		std::vector<std::string> names;
		for (auto child : children) {
			names.push_back( child->getName() );
		}
		return std::any(names);
	}
	return std::any(0);
}
