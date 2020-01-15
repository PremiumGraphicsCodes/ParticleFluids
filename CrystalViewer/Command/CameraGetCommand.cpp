#include "CameraGetCommand.h"

#include "Public/CameraGetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraGetCommand::Results::Results() :
	near(CameraGetCommandLabels::NearLabel, 0.1),
	far(CameraGetCommandLabels::FarLabel, 1.0),
	eyePosition(CameraGetCommandLabels::EyePositionLabel, Vector3dd(1,1,1)),
	targetPosition(CameraGetCommandLabels::TargetPositionLabel, Vector3dd(0,0,0)),
	upVector(CameraGetCommandLabels::UpVectorLabel, Vector3dd(0,1,0)),
	projectionMatrix(CameraGetCommandLabels::ProjectionMatrixLabel, Matrix4dd()),
	rotationMatrix(CameraGetCommandLabels::RotationMatrixLabel, Matrix4dd())
{
	add(&near);
	add(&far);
	add(&eyePosition);
	add(&targetPosition);
	add(&upVector);
	add(&projectionMatrix);
	add(&rotationMatrix);
}

std::string CameraGetCommand::getName()
{
	return CameraGetCommandLabels::CommandNameLabel;
}

void CameraGetCommand::execute(World* scene)
{
	auto camera = scene->getRenderer()->getCamera();
	results.near.setValue(camera->getNear());
	results.far.setValue(camera->getFar());
	results.eyePosition.setValue(camera->getEye());
	results.targetPosition.setValue(camera->getTarget());
	results.upVector.setValue(camera->getUp());
	results.projectionMatrix.setValue(camera->getProjectionMatrix());
	results.rotationMatrix.setValue(camera->getRotationMatrix());
}