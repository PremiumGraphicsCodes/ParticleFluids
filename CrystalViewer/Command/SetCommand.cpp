#include "SetCommand.h"

#include "Public/SetLabels.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "../../Crystal/Scene/FaceGroupScene.h"
#include "../../Crystal/Scene/LightScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void SetCommand::Set(World* world, const std::string& name, std::any value)
{
	if (name == SetLabels::CameraPositionLabel) {
		const auto& pos = std::any_cast<Vector3dd>(value);
		world->getRenderer()->getCamera()->setEye(pos);
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
	else if (scene->getType() == SceneType::FaceGroupScene) {
		auto faceGroup = world->getObjects()->findSceneById<FaceGroupScene*>(id);
		if (name == SetLabels::MaterialNameLabel) {
			faceGroup->setMaterialName(std::any_cast<std::string>(value));
		}
	}
	else if (scene->getType() == SceneType::LightScene) {
		auto light = world->getObjects()->findSceneById<LightScene*>(id);
		auto l = light->getLight();
		if (name == SetLabels::AmbientLabel) {
			l.setAmbient(std::any_cast<Graphics::ColorRGBAf>(value));
			light->setLight(l);
		}
		else if (name == SetLabels::DiffuseLabel) {
			l.setDiffuse(std::any_cast<Graphics::ColorRGBAf>(value));
			light->setLight(l);
		}
		else if (name == SetLabels::SpecularLabel) {
			l.setSpecular(std::any_cast<Graphics::ColorRGBAf>(value));
			light->setLight(l);
		}
		else if (name == SetLabels::PositionLabel) {
			l.setPosition(std::any_cast<Vector3dd>(value));
			light->setLight(l);
		}
	}
}
