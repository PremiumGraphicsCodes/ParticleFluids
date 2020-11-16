#pragma once

#include "../../CrystalViewer/AppBase/IMenu.h"

namespace Crystal {
	namespace UI {

class OpenVDBMenu : public IMenu
{
public:
	OpenVDBMenu(const std::string& name, Scene::World* model, Canvas* canvas);

	void onShow() override;
};
	}
}