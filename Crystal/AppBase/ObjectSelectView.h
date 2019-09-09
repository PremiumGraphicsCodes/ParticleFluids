#pragma once

#include "IPanel.h"

#include "../Scene/World.h"

namespace Crystal {
	namespace UI {

class ObjectSelectView : public IPanel
{
public:
	ObjectSelectView(const std::string& name, Scene::World* model, Canvas* canvas) :
		IPanel(name, model, canvas),
		id(0),
		type(Scene::SceneType::All)
	{
	}

	ObjectSelectView(const std::string& name, Scene::World* model, Canvas* canvas, const Scene::SceneType type) :
		IPanel(name, model, canvas),
		id(0),
		type(type)
	{
	}

	void onShow() override;

	int getId() const { return id; }

private:
	int id;
	Scene::SceneType type;
};

	}
}