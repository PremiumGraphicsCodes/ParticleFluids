#include "TranslateCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/TransformLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TranslateCommand::Args::Args() :
	id(TransformLabels::IdLabel, -1),
	vector(TransformLabels::TranslateLabel, Math::Vector3dd())
{
	add(&id);
	add(&vector);
}


std::string TranslateCommand::getName()
{
	return TransformLabels::TranslateCommandLabel;
}

void TranslateCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	const auto& v = args.vector.getValue();
	const Matrix4dd matrix
	(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		v.x, v.y, v.z, 1
	);
	scene->setMatrix(matrix);
}
