#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class WireFramePanel : public IPanel
{
public:
	WireFramePanel(const std::string& name, Repository* model, Canvas* canvas);
};

	}
}