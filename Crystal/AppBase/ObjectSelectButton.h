#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

class ObjectSelectButton : public IPopupButton
{
public:
	ObjectSelectButton(const std::string& name, RootScene* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		id(0),
		type(Scene::SceneType::All)
	{
	}

	ObjectSelectButton(const std::string& name, RootScene* model, Canvas* canvas, const Scene::SceneType type) :
		IPopupButton(name, model, canvas),
		id(0),
		type(type)
	{
	}


	void onShow() override;

	void onOk() override;

	void onCancel() override;

	int getId() const { return id; }

private:
	int id;
	Scene::SceneType type;
};

	}
}