#pragma once

#include "IWindow.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../Scene/LightScene.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class LightEditView : public IWindow
{
public:
	LightEditView(const std::string& name, Scene::RootScene* repository, Canvas* canvas);

	void setValue(Scene::LightScene* value);

	void show() override;

	//void setVisible(const bool isVisible) { this->isVisible = isVisible; }

private:
	IntView id;
	LightView light;
	StringView name;
	Button editButton;
	Scene::RootScene* repository;
	Canvas* canvas;
};

	}
}
