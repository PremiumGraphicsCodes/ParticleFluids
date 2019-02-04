#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name, Repository* model, Canvas* canvas) :
		IMenu(name, model, canvas)
	{}

	virtual void show() override;
};

	}
}