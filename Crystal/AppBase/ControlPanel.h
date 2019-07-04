#pragma once

#include "IPanel.h"
#include <memory>

namespace Crystal {
	namespace UI {

class ControlPanel : public IPanel
{
public:
	ControlPanel(const std::string& name, Repository* model, Canvas* canvas);

	void setWindow(IWindow* view)
	{
		children.clear();
		children.push_back(view);
	}

	//void show() override;

private:
	//IWindow* view;
};

	}
}