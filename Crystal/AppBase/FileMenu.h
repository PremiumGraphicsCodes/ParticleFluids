#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class FileMenu : public IMenu
{
public:
	FileMenu(const std::string& name, Scene::RootScene* model, Canvas* canvas) :
		IMenu(name,model, canvas)
	{}

	virtual void show() override;
};
	}
}