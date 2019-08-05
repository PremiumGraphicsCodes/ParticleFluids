#include "IShaderScene.h"

using namespace Crystal::Scene;

IShaderScene* IShaderScene::findSceneById(int id)
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

IShaderScene* IShaderScene::findSceneByName(const std::string& name)
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
