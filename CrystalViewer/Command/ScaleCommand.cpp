#include "ScaleCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/TransformLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ScaleCommand::Args::Args() :
	id(TransformLabels::IdLabel, -1),
	ratio(TransformLabels::ScaleRatioLabel, Math::Vector3dd())
{
	add(&id);
	add(&ratio);
}


std::string ScaleCommand::getName()
{
	return TransformLabels::ScaleCommandLabel;
}

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
