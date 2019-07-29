#pragma once

#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class PolygonMeshPanel : public IPanel
{
public:
	PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control);

	void show() override;

private:
	Button box;
};
	}
}