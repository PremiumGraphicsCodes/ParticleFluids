#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class WireFramePanel : public IPanel
{
public:
	WireFramePanel(Model* model, Canvas* canvas);

	void show() override;
};

	}
}