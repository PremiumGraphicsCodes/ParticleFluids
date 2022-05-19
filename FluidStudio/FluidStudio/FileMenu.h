#pragma once

#include "CrystalScene/AppBase/IMenu.h"

namespace PG {
	namespace FS {

class FileMenu : public Crystal::UI::IMenu
{
public:
	FileMenu(const std::string& name, Crystal::Scene::World* world, Crystal::UI::Canvas* canvas);

private:
	void onOpen();

	void onSave();
};

	}
}