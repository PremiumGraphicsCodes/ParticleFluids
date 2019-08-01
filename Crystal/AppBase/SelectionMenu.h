#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class SelectionMenu : public IMenu
{
public:
	SelectionMenu(const std::string& name, Scene::RootScene* model, Canvas* canvas, ControlPanel* control) :
		IMenu(name, model, canvas),
		control(control)
	{}

	virtual void show() override;

private:
	ControlPanel* control;
};

	}
}