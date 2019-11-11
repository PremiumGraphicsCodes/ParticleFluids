#include "TransformCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/TransformLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TransformCommand::Args::Args() :
	id(TransformLabels::IdLabel, -1),
	matrix(TransformLabels::MatrixLabel, Math::Matrix4dd())
{
	add(&id);
	add(&matrix);
}

std::string TransformCommand::getName()
{
	return TransformLabels::TransformCommandLabel;
}

void TransformCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->transform(args.matrix.getValue());
}
