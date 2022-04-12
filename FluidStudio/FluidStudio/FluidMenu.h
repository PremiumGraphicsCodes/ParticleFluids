#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class FluidMenu : public IMenu
{
public:
	FluidMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

private:
	ControlPanel* control;
};

	}
}
