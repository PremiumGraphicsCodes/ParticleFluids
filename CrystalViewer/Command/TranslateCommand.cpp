#include "TranslateCommand.h"

#include "../Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

void TranslateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->translate(args.vector.getValue());
}
