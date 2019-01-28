#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class CameraMenu : public IMenu
{
public:
	CameraMenu(const std::string& name, Model* model, Canvas* canvas) :
		IMenu(name, model, canvas)
	{}

	virtual void show() override;
};

	}
}