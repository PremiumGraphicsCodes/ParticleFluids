#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace PG {
	namespace FS {
		class MainModel;
	}
}

namespace Crystal {
	namespace UI {

class FluidMenu : public IMenu
{
public:
	FluidMenu(const std::string& name, Scene::World* world, Canvas* canvas, ControlPanel* control, PG::FS::MainModel* model);

private:
	ControlPanel* control;
};

	}
}
