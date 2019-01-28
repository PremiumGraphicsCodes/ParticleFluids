#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class AppearancePanel : public IPanel
{
public:
	AppearancePanel(const std::string& name, Model* model, Canvas* canvas);
};

	}
}