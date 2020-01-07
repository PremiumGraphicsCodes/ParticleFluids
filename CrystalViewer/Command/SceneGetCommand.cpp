#include "SceneGetCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SceneGetCommand::Args::Args() :
	id("Id", -1)
{
	add(&id);
}

SceneGetCommand::Results::Results() :
	//center("Center", Vector3dd(0,0,0)),
	boundingBox("BoundingBox", Box3d())
{
	//add(&center);
	add(&boundingBox);
}

std::string SceneGetCommand::getName()
{
	return "SceneGet";
}

SceneGetCommand::SceneGetCommand() :
	ICommand(&args, &results)
{
}

void SceneGetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById(args.id.getValue());
	if (scene == nullptr) {
		return;
	}
	results.boundingBox.setValue( scene->getBoundingBox() );
}
