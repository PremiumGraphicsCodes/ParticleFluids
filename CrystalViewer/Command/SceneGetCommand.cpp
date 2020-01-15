#include "SceneGetCommand.h"

#include "Public/SceneGetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SceneGetCommand::Args::Args() :
	id(SceneGetLabels::IdLabel, -1)
{
	add(&id);
}

SceneGetCommand::Results::Results() :
	//center("Center", Vector3dd(0,0,0)),
	isVisible(SceneGetLabels::IsVisibleLabel, false),
	name(SceneGetLabels::NameLabel, std::string()),
	boundingBox(SceneGetLabels::BoundingBoxLabel, Box3d())
{
	//add(&center);
	add(&name);
	add(&isVisible);
	add(&boundingBox);
}

std::string SceneGetCommand::getName()
{
	return SceneGetLabels::CommandLabel;
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
	results.isVisible.setValue(scene->isVisible());
	results.name.setValue(scene->getName());
}
