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
	isPickable(SceneGetLabels::IsPickableLabel, false),
	name(SceneGetLabels::NameLabel, std::string()),
	boundingBox(SceneGetLabels::BoundingBoxLabel, Box3d()),
	type(SceneGetLabels::TypeLabel, SceneType::None)
{
	//add(&center);
	add(&isVisible);
	add(&isPickable);
	add(&name);
	add(&boundingBox);
	add(&type);
}

std::string SceneGetCommand::getName()
{
	return SceneGetLabels::CommandLabel;
}

SceneGetCommand::SceneGetCommand() :
	ICommand(&args, &results)
{
}

bool SceneGetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	results.boundingBox.setValue( scene->getBoundingBox() );
	results.isVisible.setValue(scene->isVisible());
	results.isPickable.setValue(scene->isPickable());
	results.name.setValue(scene->getName());
	results.type.setValue(scene->getType());
	return true;
}
