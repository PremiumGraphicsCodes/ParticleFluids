#pragma once

#include "../../Crystal/AppBase/IMenu.h"
#include "../../Crystal/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class AlgoMenu : public IMenu
{
public:
	AlgoMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control);

	void onShow() override;

private:
	ControlPanel* control;
};

	}
}
