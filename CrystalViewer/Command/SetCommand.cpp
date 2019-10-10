#include "SetCommand.h"

#include "../../Crystal/Scene/ParticleAttribute.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void SetCommand::Set(World* world, const std::string& name, std::any value)
{
	if (name == "CameraPosition") {
		const auto& pos = std::any_cast<Vector3dd>(value);
		world->getRenderer()->getCamera()->moveTo(pos);
	}
	else if (name == "CameraProjectionMatrix") {
		const auto& pos = std::any_cast<Matrix4dd>(value);
		world->getRenderer()->getCamera()->setRotation(pos);
	}
}

void SetCommand::Set(World* world, int id, const std::string& name, std::any value)
{
	auto scene = world->getObjects()->findSceneById(id);
	if (scene->getType() == SceneType::ParticleSystemScene) {
		ParticleAttribute attr;
		std::string name = scene->getName();
		if (name == "PointSize") {
			attr.size = std::any_cast<float>(value);
		}
		else if (name == "Color") {
			attr.color = std::any_cast<Graphics::ColorRGBAf>(value);
		}
		/*
		else if (name == "Name") {
			std::any_cast<std::string>(value);
		}
		*/
	}
}
