#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class ShapeMenu : public IMenu
{
public:
	ShapeMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
		IMenu(name, model, canvas),
		control(control)
	{}

	void onShow() override;

private:
	ControlPanel* control;
};

	}
}