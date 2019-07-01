#include "IScene.h"

using namespace Crystal::Model;

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
