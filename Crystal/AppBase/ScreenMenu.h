#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class ScreenMenu : public IMenu
{
public:
	ScreenMenu(const std::string& name, Repository* model, Canvas* canvas) :
		IMenu(name, model, canvas)
	{}

	virtual void show() override;
};

	}
}