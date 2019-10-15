#include "TranslateCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/TransformLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

TranslateCommand::Args::Args() :
	id(::IdLabel, -1),
	vector(::TranslateLabel, Math::Vector3dd())
{
	add(&id);
	add(&vector);
}


std::string TranslateCommand::getName()
{
	return ::TransformCommandLabel;
}

void TranslateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->translate(args.vector.getValue());
}
