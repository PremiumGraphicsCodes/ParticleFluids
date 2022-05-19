#pragma once

#include "CrystalScene/AppBase/IMenu.h"
#include "CrystalScene/AppBase/ControlPanel.h"

namespace PG {
	namespace FS {

class VDBMenu : public Crystal::UI::IMenu
{
public:
	VDBMenu(const std::string& name, Crystal::Scene::World* model, Crystal::UI::Canvas* canvas, Crystal::UI::ControlPanel* control);

private:
	Crystal::UI::ControlPanel* control;
};

	}
}
