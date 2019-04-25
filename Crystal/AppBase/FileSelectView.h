#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class FileSelectView : public IWindow
{
public:
	explicit FileSelectView(const std::string& name) :
		IWindow(name)
	{}

	void show() override;
};

	}
}