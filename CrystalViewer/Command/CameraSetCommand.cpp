#include "CameraSetCommand.h"

#include "Public/CameraSetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraSetCommand::Args::Args() :
	eyePosition(CameraSetCommandLabels::EyePositionLabel, Vector3dd(0, 0, 0))
{
	add(&eyePosition);
}

std::string CameraSetCommand::getName()
{
	return CameraSetCommandLabels::CommandLabel;
}

void CameraSetCommand::execute(World* world)
{
	const auto& pos = std::any_cast<Vector3dd>(args.eyePosition);
	world->getRenderer()->getCamera()->setEye(pos);
}