#include "RotateCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/TransformLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

RotateCommand::Args::Args() :
	id(::IdLabel, -1),
	matrix(::MatrixLabel, Math::Matrix3dd())
{
	add(&id);
	add(&matrix);
}

std::string RotateCommand::getName()
{
	return ::RotateCommandLabel;
}

void RotateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->transform(args.matrix.getValue());
}
