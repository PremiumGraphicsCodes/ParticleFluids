#include "CameraRotateCommand.h"
#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraRotateCommand::Args::Args() :
	matrix(CameraRotateCommandLabels::MatrixLabel, Matrix3dd())
{
	add(&matrix);
}

std::string CameraRotateCommand::getName()
{
	return CameraRotateCommandLabels::CameraRotateCommandLabel;
}

void CameraRotateCommand::execute(World* scene)
{
	Matrix3df matrix = args.matrix.getValue();
	auto camera = scene->getRenderer()->getCamera();
	camera->rotate(matrix);
}
