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