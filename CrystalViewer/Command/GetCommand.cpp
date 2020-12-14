#include "GetCommand.h"

#include "Public/GetLabels.h"

#include "../../Crystal/Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;


std::any GetCommand::Get(World* world, const std::string& name)
{
	if (name == GetLabels::SceneCountLabel) {
		return static_cast<int>( world->getScenes()->getRoot()->getChildren().size() );
	}
	else if (name == GetLabels::SceneListIdsLabel) {
		const auto& children = world->getScenes()->getRoot()->getChildren();
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
	auto scene = world->getScenes()->findSceneById(id);
	if (name == GetLabels::SceneCountLabel) {
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
	/*
	else if (scene->getType() == SceneType::FaceGroupScene) {
		auto faceGroup = world->getScenes()->findSceneById<FaceGroupScene*>(id);
		return std::any( faceGroup->getMaterial()->get Name() );
	}
	*/

	assert(false);
	return std::any(0);
}
