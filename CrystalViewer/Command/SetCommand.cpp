#include "SetCommand.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "Public/SetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void SetCommand::Set(World* world, const std::string& name, std::any value)
{
	if (name == SetLabels::CameraPositionLabel) {
		const auto& pos = std::any_cast<Vector3dd>(value);
		world->getRenderer()->getCamera()->setEye(pos);
	}
	else if (name == SetLabels::CameraProjectionMatrixLabel ) {
		const auto& pos = std::any_cast<Matrix4dd>(value);
		world->getRenderer()->getCamera()->setRotationMatrix(pos);
	}
}

void SetCommand::Set(World* world, int id, const std::string& name, std::any value)
{
	auto scene = world->getObjects()->findSceneById(id);
	if (scene->getType() == SceneType::ParticleSystemScene) {
		ParticleAttribute attr;
//		std::string name = scene->getName();
		if (name == SetLabels::PointSizeLabel) {
			attr.size = std::any_cast<float>(value);
		}
		else if (name == SetLabels::ColorLabel) {
			attr.color = std::any_cast<Graphics::ColorRGBAf>(value);
		}
		else if (name == SetLabels::IsVisibleLabel) {
			scene->_isVisible = std::any_cast<bool>(value);
		}
		else if (name == SetLabels::NameLabel) {
			scene->setName( std::any_cast<std::string>(value) );
		}
	}
	else if (scene->getType() == SceneType::WireFrameScene) {
		if (name == SetLabels::IsVisibleLabel) {
			scene->_isVisible = std::any_cast<bool>(value);
		}
		else if (name == SetLabels::NameLabel) {
			scene->setName(std::any_cast<std::string>(value));
		}
	}
}
