#include "RotateCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/TransformLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

RotateCommand::Args::Args() :
	id(TransformLabels::IdLabel, -1),
	matrix(TransformLabels::MatrixLabel, Math::Matrix3dd())
{
	add(&id);
	add(&matrix);
}

std::string RotateCommand::getName()
{
	return TransformLabels::RotateCommandLabel;
}

void RotateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->transform(args.matrix.getValue());
}
