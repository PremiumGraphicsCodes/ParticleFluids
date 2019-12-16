#include "GetCommand.h"

#include "Public/GetLabels.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


std::any GetCommand::Get(World* world, const std::string& name)
{
	if (name == GetLabels::CameraEyePositionLabel) {
		const auto& pos = world->getRenderer()->getCamera()->getEye();
		return std::any(pos);
	}
	else if (name == GetLabels::CameraProjectionMatrixLabel) {
		const auto& rot = world->getRenderer()->getCamera()->getProjectionMatrix();
		return std::any(rot);
	}
	else if (name == GetLabels::CameraRotationMatrixLabel) {
		const auto& rot = world->getRenderer()->getCamera()->getRotationMatrix();
		return std::any(rot);
	}
	else if (name == GetLabels::BoundingBoxLabel) {
		const auto& bb = world->getBoundingBox();
		return std::any(bb);
	}
	else if (name == GetLabels::SceneCountLabel) {
		return static_cast<int>( world->getObjects()->getRoot()->getChildren().size() );
	}
	else if (name == GetLabels::SceneListIdsLabel) {
		const auto& children = world->getObjects()->getRoot()->getChildren();
		std::vector<int> ids;
		for (auto child : children) {
			ids.push_back(child->getId());
		}
		return std::any(ids);
	}

	return std::any(0);
}

std::any GetCommand::Get(World* world, int id, const std::string& name)
{
	auto scene = world->getObjects()->findSceneById(id);
	if (name == GetLabels::SceneTypeLabel) {
		return std::any(scene->getType());
	}
	else if (name == GetLabels::NameLabel) {
		return std::string(scene->getName());
	}
	else if (name == GetLabels::IsVisibleLabel) {
		return std::any(scene->isVisible());
	}
	else if (name == GetLabels::BoundingBoxLabel) {
		auto shapeScene = world->getObjects()->findSceneById<IShapeScene*>(id);		
		return std::any(shapeScene->getShape()->getBoundingBox());
	}
	else if (name == GetLabels::IsPickableLabel) {
		return std::any(scene->isPickable());
	}
	else if (name == GetLabels::SceneCountLabel) {
		return static_cast<int>(scene->getChildren().size());
	}
	else if (name == GetLabels::SceneListIdsLabel) {
		const auto& children = scene->getChildren();
		std::vector<int> ids;
		for (auto child : children) {
			ids.push_back(child->getId());
		}
		return std::any(ids);
	}

	assert(false);
	return std::any(0);
}

std::any GetCommand::Get(World* world, int parentId, int childId, const std::string& name)
{
	if (name == GetLabels::PositionLabel) {
		auto scene = world->getObjects()->findSceneById<Crystal::Scene::IShapeScene*>(parentId);
		return std::any( scene->getPosition(childId) );
	}
	return std::any(0);
}

