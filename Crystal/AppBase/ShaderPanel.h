#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ShaderPanel : public IPanel
{
public:
	ShaderPanel(const std::string& name, Repository* model, Canvas* canvas);
};

	}
}