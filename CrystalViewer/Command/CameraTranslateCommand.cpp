#include "CameraTranslateCommand.h"
#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraTranslateCommand::Args::Args() :
	translate(CameraTranslateCommandLabels::TranslateLabel, Vector3dd())
{
	add(&translate);
}

std::string CameraTranslateCommand::getName()
{
	return CameraTranslateCommandLabels::CameraTranslateCommandLabel;
}

void CameraTranslateCommand::execute(World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	camera->moveEye(args.translate.getValue());
	camera->moveTarget(args.translate.getValue());
}
