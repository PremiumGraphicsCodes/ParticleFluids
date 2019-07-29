#pragma once

#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {
		class ControlPanel;

class ParticleSystemPanel : public IPanel
{
public:
	ParticleSystemPanel(const std::string& name, Repository* model, Canvas* canvas, ControlPanel* control);

	void show() override;

private:
	ControlPanel* control;
	Button box;
	Button cone;
	Button cylinder;
	Button sphere;
};

	}
}