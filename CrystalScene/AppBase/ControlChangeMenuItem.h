#pragma once

#include "IMenuItem.h"
#include "ControlPanel.h"

namespace Crystal {
	namespace UI {

class ControlChangeMenuItem : public IMenuItem
{
public:
	ControlChangeMenuItem(const std::string& name, ControlPanel* control, IWindow* window) :
		IMenuItem(name),
		control(control),
		window(window)
	{}

protected:
	void onPushed() override
	{
		control->setWindow(window);
	}

private:
	ControlPanel* control;
	IWindow* window;
};

	}
}