#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class AppearancePanel : public IPanel
{
public:
	AppearancePanel(Model* model, Canvas* canvas) :
		IPanel(model, canvas)
	{}

	void show() override;
};

	}
}