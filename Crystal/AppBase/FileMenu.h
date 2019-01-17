#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class FileMenu : public IMenu
{
public:
	FileMenu(Model* model, ICanvas* canvas) :
		IMenu(model, canvas)
	{}

	virtual void show() override;
};
	}
}