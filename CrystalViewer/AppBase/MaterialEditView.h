#pragma once

#include "IPopupButton.h"
#include "MaterialView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class MaterialEditView : public IWindow
{
public:
	MaterialEditView(const std::string& name, Scene::World* model, Canvas* canvas);

	void setValue(Scene::MaterialScene* value);

	void onShow() override;

private:
	IntView id;
	MaterialView material;
	StringView name;
	Scene::World* repository;
	Canvas* canvas;
	Button editButton;
};

	}
}
