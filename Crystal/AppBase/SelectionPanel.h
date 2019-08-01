#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class SelectionPanel : public IPanel
{
public:
	SelectionPanel(const std::string& name, RootScene* model, Canvas* canvas);
};

	}
}