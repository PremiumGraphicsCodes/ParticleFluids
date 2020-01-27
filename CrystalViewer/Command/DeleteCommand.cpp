#include "DeleteCommand.h"

#include "Public/DeleteLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string DeleteCommand::getName()
{
	return DeleteLabels::CommandNameLabel;
}

DeleteCommand::Args::Args() :
	id(DeleteLabels::IdLabel, -1),
	isItem(DeleteLabels::IsItemLabel, false)
{
	add(&id);
	add(&isItem);
}

DeleteCommand::DeleteCommand() :
	ICommand(&args, nullptr)
{}

bool DeleteCommand::execute(World* world)
{
	if (args.isItem.getValue()) {
		auto scene = world->getItems()->findSceneById(args.id.getValue());
		if (scene == nullptr) {
			return false;
		}
		world->getItems()->deleteSceneById(args.id.getValue());
	}
	else {
		auto scene = world->getObjects()->findSceneById(args.id.getValue());
		if (scene == nullptr) {
			return false;
		}
		world->getObjects()->deleteSceneById(args.id.getValue());
	}
	return true;
}
