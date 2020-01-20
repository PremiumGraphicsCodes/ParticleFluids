#pragma once

#include "IView.h"
#include "IPopupButton.h"
#include "MaterialView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class MaterialEditView : public IView
{
public:
	MaterialEditView(const std::string& name, Scene::World* model, Canvas* canvas);

	void setValue(Scene::MaterialScene* value);

private:
	IntView id;
	MaterialView material;
	StringView name;
	Scene::World* world;
	Canvas* canvas;
	Button editButton;
};

	}
}
