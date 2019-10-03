#include "CameraTranslateCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraTranslateCommand::Args::Args() :
	translate("Translate", Vector3dd())
{
	add(&translate);
}

void CameraTranslateCommand::execute(World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	camera->move(args.translate.getValue());
}
