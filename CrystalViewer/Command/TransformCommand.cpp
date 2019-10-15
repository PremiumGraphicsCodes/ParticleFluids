#include "TransformCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string TransformCommand::getName()
{
	return "Transform";
}

void TransformCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->transform(args.matrix.getValue());
}
