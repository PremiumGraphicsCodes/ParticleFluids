#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class FileMenu : public IMenu
{
public:
	FileMenu(Model* model, Canvas* canvas) :
		IMenu("File",model, canvas)
	{}

	virtual void show() override;
};
	}
}