#include "CameraZoomCommand.h"
#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

CameraZoomCommand::Args::Args() :
	ratio(CameraZoomCommandLabels::ZoomRatioLabel, 1.0)
{
	add(&ratio);
}

std::string CameraZoomCommand::getName()
{
	return CameraZoomCommandLabels::CameraZoomCommandLabel;
}

void CameraZoomCommand::execute(Crystal::Scene::World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	camera->zoom(args.ratio.getValue());
}

