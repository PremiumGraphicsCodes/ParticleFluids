#include "BuildCommand.h"

#include "Public/BuildLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string BuildCommand::getName()
{
	return BuildLabels::CommandNameLabel;
}

BuildCommand::Args::Args() :
	id(BuildLabels::IdLabel, -1),
	layer(BuildLabels::LayerLabel, 0)
{
	add(&id);
	add(&layer);
}

BuildCommand::BuildCommand() :
	ICommand(&args, nullptr)
{}

bool BuildCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById(args.id.getValue());
	scene->build(*world->getGLFactory());
	return true;
}
