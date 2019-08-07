#pragma once

#include "../../Crystal/AppBase/IMenu.h"
#include "../../Crystal/AppBase/ControlPanel.h"

namespace Crystal {
	namespace UI {

class AlgoMenu : public IMenu
{
public:
	AlgoMenu(const std::string& name, Scene::RootScene* model, Canvas* canvas, ControlPanel* control);

	void show() override;

private:
	ControlPanel* control;
};

	}
}
