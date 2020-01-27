#include "SetMatrixCommand.h"

#include "../../Crystal/Scene/IShapeScene.h"
#include "Public/SetMatrixLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SetMatrixCommand::Args::Args() :
	id(SetMatrixLabels::IdLabel, -1),
	matrix(SetMatrixLabels::MatrixLabel, Math::Matrix4dd())
{
	add(&id);
	add(&matrix);
}

std::string SetMatrixCommand::getName()
{
	return SetMatrixLabels::CommandLabel;
}

bool SetMatrixCommand::execute(World* world)
{
	auto scene = world->getObjects()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	scene->setMatrix(args.matrix.getValue());

	return true;
}
