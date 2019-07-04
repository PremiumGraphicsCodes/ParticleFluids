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
		if (c->findSceneById(id) != nullptr) {
			return c;
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
