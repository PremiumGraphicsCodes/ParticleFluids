#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class MaskMenu : public IMenu
{
public:
	MaskMenu(const std::string& name, Repository* model, Canvas* canvas) :
		IMenu(name, model, canvas)
	{}

	virtual void show() override;
};

	}
}
