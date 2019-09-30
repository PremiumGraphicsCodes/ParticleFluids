#include "CameraFitCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void CameraFitCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getRenderer()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->setTarget(boundingBox.getCenter());
	camera->moveTo(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0));
}

void CameraXYCommand::execute(World* world)
{
	CameraFitCommand fitCommand;
	fitCommand.execute(world);
	auto camera = world->getRenderer()->getCamera();
	camera->setRotation(
		Math::Matrix4dd
		(
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		)
	);
}

void CameraYZCommand::execute(World* world)
{
	CameraFitCommand fitCommand;
	fitCommand.execute(world);
	auto camera = world->getRenderer()->getCamera();
	camera->rotate(glm::radians(90.0f), 0.0);
}

void CameraZXCommand::execute(World* world)
{
	CameraFitCommand fitCommand;
	fitCommand.execute(world);
	auto camera = world->getRenderer()->getCamera();
	camera->rotate(0.0, glm::radians(90.0f));
}
