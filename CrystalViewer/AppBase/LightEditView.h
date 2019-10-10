#pragma once

#include "IWindow.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../../Crystal/Scene/LightScene.h"
#include "../../Crystal/Scene/World.h"
#include "Canvas.h"

namespace Crystal {
	namespace UI {

class LightEditView : public IWindow
{
public:
	LightEditView(const std::string& name, Scene::World* repository, Canvas* canvas);

	void setValue(Scene::LightScene* value);

	void onShow() override;

	//void setVisible(const bool isVisible) { this->isVisible = isVisible; }

private:
	IntView id;
	LightView light;
	StringView name;
	Button editButton;
	Scene::World* repository;
	Canvas* canvas;
};

	}
}
