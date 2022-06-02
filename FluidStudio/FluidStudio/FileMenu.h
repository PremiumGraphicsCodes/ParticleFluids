#pragma once

#include "CrystalScene/AppBase/IMenu.h"

namespace PG {
	namespace FS {
		class MainModel;

class FileMenu : public Crystal::UI::IMenu
{
public:
	FileMenu(const std::string& name, Crystal::Scene::World* world, Crystal::UI::Canvas* canvas, MainModel* model);

private:
	void onOpen();

	void onSave();

	MainModel* model;
};

	}
}