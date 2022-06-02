#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace PG {
	namespace FS {
		class MainModel;

class FluidMenu : public Crystal::UI::IMenu
{
public:
	FluidMenu(const std::string& name, Crystal::Scene::World* world, Crystal::UI::Canvas* canvas, Crystal::UI::ControlPanel* control, PG::FS::MainModel* model);

private:
	Crystal::UI::ControlPanel* control;
};

	}
}
