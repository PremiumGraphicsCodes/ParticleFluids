#pragma once

#include "IPanel.h"

#include "../Scene/RootScene.h"

namespace Crystal {
	namespace UI {

class ObjectSelectView : public IPanel
{
public:
	ObjectSelectView(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IPanel(name, model, canvas),
		id(0),
		type(Scene::SceneType::All)
	{
	}

	ObjectSelectView(const std::string& name, Scene::RootScene* model, Canvas* canvas, const Scene::SceneType type) :
		IPanel(name, model, canvas),
		id(0),
		type(type)
	{
	}

	void show() override;

	int getId() const { return id; }

private:
	int id;
	Scene::SceneType type;
};

	}
}