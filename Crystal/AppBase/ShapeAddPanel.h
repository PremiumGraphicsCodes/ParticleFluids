#pragma once

#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class ShapeAddPanel : public IPanel
{
public:
	ShapeAddPanel(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control);

	void show() override;

private:
	ControlPanel* control;
	Button psBox;
	Button psCone;
	Button psCylinder;
	Button psSphere;
};

	}
}