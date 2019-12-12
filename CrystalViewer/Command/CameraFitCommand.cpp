#include "CameraFitCommand.h"

#include "Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string CameraFitCommand::getName()
{
	return CameraFitCommandLabels::CameraFitCommandLabel;
}

void CameraFitCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getRenderer()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0), boundingBox.getCenter(), Vector3dd(0,1,0));
}

std::string CameraXYCommand::getName()
{
	return CameraFitCommandLabels::CameraXYCommandLabel;
}

void CameraXYCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getRenderer()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0), boundingBox.getCenter(), Vector3dd(0, 1, 0));
}

std::string CameraYZCommand::getName()
{
	return CameraFitCommandLabels::CameraYZCommandLabel;
}

void CameraYZCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getRenderer()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(dist * 2.0, 0, 0), boundingBox.getCenter(), Vector3dd(0, 0, 1));
}

std::string CameraZXCommand::getName()
{
	return CameraFitCommandLabels::CameraZXCommandLabel;
}

void CameraZXCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getRenderer()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, dist * 2.0, 0), boundingBox.getCenter(), Vector3dd(1, 0, 0));
}
