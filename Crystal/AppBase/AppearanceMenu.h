#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class AppearanceMenu : public IMenu
{
public:
	AppearanceMenu(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control) :
		IMenu(name, model, canvas),
		control(control)
	{}

	virtual void show() override;

private:
	ControlPanel* control;
};

	}
}