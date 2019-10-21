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
	/*
	else if (name == "CameraScale") {
		const auto& rot = world->getRenderer()->getCamera()->setS();
		return std::any(rot);
	}
	*/
	else if (name == "SceneCount") {
		return static_cast<int>( world->getObjects()->getRoot()->getChildren().size() );
	}
	else if (name == "SceneList") {
		const auto& children = world->getObjects()->getRoot()->getChildren();
		std::vector<std::string> names;
		for (auto child : children) {
			names.push_back( child->getName() );
		}
		return std::any(names);
	}
	else if (name == "SceneListIds") {
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
	if (name == "SceneTypeId") {
		return static_cast<int>(scene->getType());
	}
	else if (name == "Name") {
		return std::string(scene->getName());
	}
	else if (name == "IsVisible") {
		return std::any(scene->isVisible());
	}
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

