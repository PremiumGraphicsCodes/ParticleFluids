#include "GetCommand.h"

#include "Public/GetLabels.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


std::any GetCommand::Get(World* world, const std::string& name)
{
	if (name == ::CameraPositionLabel) {
		const auto& pos = world->getRenderer()->getCamera()->getPosition();
		return std::any(pos);
	}
	else if (name == ::CameraProjectionMatrixLabel) {
		const auto& rot = world->getRenderer()->getCamera()->getProjectionMatrix();
		return std::any(rot);
	}
	else if (name == ::SceneCountLabel) {
		return static_cast<int>( world->getObjects()->getRoot()->getChildren().size() );
	}
	else if (name == ::SceneListIdsLabel) {
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
	if (name == ::SceneTypeIdLabel) {
		return static_cast<int>(scene->getType());
	}
	else if (name == ::NameLabel) {
		return std::string(scene->getName());
	}
	else if (name == ::IsVisibleLabel) {
		return std::any(scene->isVisible());
	}
	assert(false);
	return std::any(0);
}

std::any GetCommand::Get(World* world, int parentId, int childId, const std::string& name)
{
	if (name == ::PositionLabel) {
		auto scene = world->getObjects()->findSceneById<Crystal::Scene::IShapeScene*>(parentId);
		return std::any( scene->getPosition(childId) );
	}
	return std::any(0);
}

