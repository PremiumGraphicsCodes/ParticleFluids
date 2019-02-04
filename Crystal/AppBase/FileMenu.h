#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class FileMenu : public IMenu
{
public:
	FileMenu(const std::string& name, Repository* model, Canvas* canvas) :
		IMenu(name,model, canvas)
	{}

	virtual void show() override;
};
	}
}