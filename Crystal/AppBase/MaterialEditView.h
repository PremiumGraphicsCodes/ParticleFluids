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
	MaterialEditView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void setValue(Scene::MaterialScene* value)
	{
		this->id.setValue(value->getId());
		this->name.setValue( value->getName() );
	}

	void show() override;


private:
	IntView id;
	MaterialView material;
	StringView name;
	Scene::RootScene* repository;
	Canvas* canvas;
	Button editButton;
};

	}
}
