#include "CameraZoomCommand.h"
#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

CameraZoomCommand::Args::Args() :
	ratio("Ratio", 1.0)
{
	add(&ratio);
}

std::string CameraZoomCommand::getName()
{
	return ::CameraZoomCommandLabel;
}

void CameraZoomCommand::execute(Crystal::Scene::World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	camera->zoom(args.ratio.getValue());
}

