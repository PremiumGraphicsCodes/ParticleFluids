#pragma once

#include "../../CrystalViewer/AppBase/IMenu.h"
#include "../../CrystalViewer/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class VDBMeshMenu : public IMenu
{
public:
	VDBMeshMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

	}
}