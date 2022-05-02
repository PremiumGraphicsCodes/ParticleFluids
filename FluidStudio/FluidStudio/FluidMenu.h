#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {
		class MainModel;

class FluidMenu : public IMenu
{
public:
	FluidMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control, MainModel* model);

private:
	ControlPanel* control;
};

	}
}
