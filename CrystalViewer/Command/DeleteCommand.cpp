#include "DeleteCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string DeleteCommand::getName()
{
	return "DeleteCommand";
}

DeleteCommand::Args::Args() :
	sceneId("SceneId", -1)
{
	add(&sceneId);
}

DeleteCommand::DeleteCommand() :
	ICommand(&args, nullptr)
{}

void DeleteCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById(args.sceneId.getValue());
	if (scene == nullptr) {
		return;
	}
	world->getObjects()->deleteSceneById(args.sceneId.getValue());
}
