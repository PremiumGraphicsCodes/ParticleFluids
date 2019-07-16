#include "IScene.h"

using namespace Crystal::Scene;

IScene::IScene() :
	id(-1),
	_isVisible(false),
	_isSelected(false),
	parent(nullptr)
{}

IScene::IScene(const int id) :
	id(id),
	_isVisible(true),
	_isSelected(false),
	parent(nullptr)
{}

IScene::IScene(const int id, const std::string& name) :
	id(id),
	name(name),
	_isVisible(true),
	_isSelected(false),
	parent(nullptr)
{}

IScene* IScene::findSceneById(int id)
{
	if (id == this->id) {
		return this;
	}
	for (auto c : children) {
		auto s = c->findSceneById(id);
		if (s != nullptr) {
			return s;
		}
	}
	return nullptr;
}

IScene* IScene::findSceneByName(const std::string& name)
{
	if (name == this->name) {
		return this;
	}
	for (auto c : children) {
		if (c->findSceneByName(name) != nullptr) {
			return c;
		}
	}
	return nullptr;
}

std::list<IScene*> IScene::findScenes(const SceneType type)
{
	std::list<IScene*> scenes;
	if (this->getType() == type) {
		scenes.push_back(this);
	}
	scenes.push_back(this);
	for (auto c : children) {
		auto ss = c->findScenes(type);
		scenes.splice(scenes.end(), ss);
	}
	return scenes;
}

