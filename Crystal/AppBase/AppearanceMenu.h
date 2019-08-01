#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class AppearanceMenu : public IMenu
{
public:
	AppearanceMenu(const std::string& name, RootScene* model, Canvas* canvas, ControlPanel* control) :
		IMenu(name, model, canvas),
		control(control)
	{}

	virtual void show() override;

private:
	ControlPanel* control;
};

	}
}