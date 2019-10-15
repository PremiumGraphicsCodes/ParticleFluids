#include "TranslateCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string TranslateCommand::getName()
{
	return "Translate";
}

void TranslateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->translate(args.vector.getValue());
}
