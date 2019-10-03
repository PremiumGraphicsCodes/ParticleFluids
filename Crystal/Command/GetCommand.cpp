#include "GetCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


std::any GetCommand::Get(World* world, const std::string& name)
{
	if (name == "CameraPosition") {
		const auto& pos = world->getRenderer()->getCamera()->getPosition();
		return std::any(pos);
	}
	else if (name == "CameraProjectionMatrix") {
		const auto& rot = world->getRenderer()->getCamera()->getProjectionMatrix();
		return std::any(rot);
	}
	/*
	else if (name == "CameraScale") {
		const auto& rot = world->getRenderer()->getCamera()->setS();
		return std::any(rot);
	}
	*/
	else if (name == "SceneCount") {
		return static_cast<int>( world->getObjects()->getRoot()->getChildren().size() );
	}

	else if (name == "SceneList") {
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

