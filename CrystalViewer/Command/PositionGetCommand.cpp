#include "PositionGetCommand.h"

#include "Public/PositionGetLabels.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PositionGetCommand::Args::Args() :
	parentId(PositionGetLabels::ParentIdLabel, -1),
	childId(PositionGetLabels::ChildIdLabel, -1)
{
	add(&parentId);
	add(&childId);
}

PositionGetCommand::Results::Results() :
	position(PositionGetLabels::PositionLabel, Vector3dd(0,0,0))
{
	add(&position);
}

std::string PositionGetCommand::getName()
{
	return PositionGetLabels::CommandNameLabel;
}

void PositionGetCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Crystal::Scene::IShapeScene*>(args.parentId.getValue());
	results.position.setValue( scene->getPosition(args.childId.getValue()));
}