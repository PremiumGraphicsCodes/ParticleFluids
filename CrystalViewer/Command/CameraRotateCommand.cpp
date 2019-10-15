#include "CameraRotateCommand.h"

#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

CameraRotateCommand::Args::Args() :
	rx(::RxLabel, 0.0),
	ry(::RyLabel, 0.0),
	rz(::RzLabel, 0.0)
{
	add(&rx);
	add(&ry);
	add(&rz);
}

std::string CameraRotateCommand::getName()
{
	return ::CameraRotateCommandLabel;
}


void CameraRotateCommand::execute(Crystal::Scene::World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	auto rx = args.rx.getValue();
	auto ry = args.ry.getValue();
	camera->rotate(rx, ry);
}

