#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name, Scene::World* model, Canvas* canvas);
};

	}
}