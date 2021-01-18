#include "SetCommand.h"

#include "Public/SetLabels.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "../../Crystal/Scene/LightScene.h"
#include "../../Crystal/Scene/MaterialScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void SetCommand::Set(World* world, int id, const std::string& name, std::any value)
{
	auto scene = world->getScenes()->findSceneById(id);
	if (scene->getType() == SceneTypeLabels::ParticleSystemScene) {
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
	else if (scene->getType() == SceneTypeLabels::WireFrameScene) {
		if (name == SetLabels::IsVisibleLabel) {
			scene->_isVisible = std::any_cast<bool>(value);
		}
		else if (name == SetLabels::NameLabel) {
			scene->setName(std::any_cast<std::string>(value));
		}
	}
}
