#include "CameraSetCommand.h"

#include "Public/CameraSetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraSetCommand::Args::Args() :
	near(CameraSetCommandLabels::NearLabel, 0.1),
	far(CameraSetCommandLabels::FarLabel, 1.0),
	eyePosition(CameraSetCommandLabels::EyePositionLabel, Vector3dd(0, 0, 1)),
	targetPosition(CameraSetCommandLabels::TargetPositionLabel, Vector3dd(0,0,0))
{
	add(&near);
	add(&far);
	add(&eyePosition);
	add(&targetPosition);
}

std::string CameraSetCommand::getName()
{
	return CameraSetCommandLabels::CommandLabel;
}

void CameraSetCommand::execute(World* world)
{
	auto camera = world->getRenderer()->getCamera();
	camera->setNear( std::any_cast<float>(args.near) );
	camera->setFar( std::any_cast<float>(args.far) );
	camera->setEye( std::any_cast<Vector3dd>(args.eyePosition) );
	camera->setTarget( std::any_cast<Vector3dd>(args.targetPosition) );
}