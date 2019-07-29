#pragma once

#include "IPanel.h"
#include "ControlPanel.h"

namespace Crystal {
	namespace UI {

class SceneAddPanel : public IPanel
{
public:
	SceneAddPanel(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control);

private:
	IPanel* control;
};

	}
}