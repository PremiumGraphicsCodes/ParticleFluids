#pragma once

#include "IWindow.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"
#include "../Scene/LightScene.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class LightEditView : public IWindow
{
public:
	LightEditView(const std::string& name, RootScene* repository, Canvas* canvas);

	void setValue(Scene::LightScene* value);

	void show() override;

	//void setVisible(const bool isVisible) { this->isVisible = isVisible; }

private:
	IntView id;
	LightView light;
	StringView name;
	Button editButton;
	RootScene* repository;
	Canvas* canvas;
};

	}
}
