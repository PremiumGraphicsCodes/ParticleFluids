#include "GetCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


std::any GetCommand::Get(World* world, const std::string& name)
{
	if (name == "CameraPosition") {
		//world->getViewModel()-
	}
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

std::any GetCommand::Get(World* world, int id, const std::string& name)
{
	return std::any(0);
}

std::any GetCommand::Get(World* world, int parentId, int childId, const std::string& name)
{
	return std::any(0);
}

