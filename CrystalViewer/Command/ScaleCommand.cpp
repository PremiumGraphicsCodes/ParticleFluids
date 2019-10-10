#include "ScaleCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void ScaleCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	const auto& ratio = args.ratio.getValue();
	Matrix3dd m(
		ratio.x, 0.0, 0.0,
		0.0, ratio.y, 0.0,
		0.0, 0.0, ratio.z);
	scene->transform(m);
}
