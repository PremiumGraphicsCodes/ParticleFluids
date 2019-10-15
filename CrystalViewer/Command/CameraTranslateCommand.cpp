#include "CameraTranslateCommand.h"
#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraTranslateCommand::Args::Args() :
	translate(::TranslateLabel, Vector3dd())
{
	add(&translate);
}

std::string CameraTranslateCommand::getName()
{
	return ::CameraTranslateCommandLabel;
}

void CameraTranslateCommand::execute(World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	camera->move(args.translate.getValue());
}
