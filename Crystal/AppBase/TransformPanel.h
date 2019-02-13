#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class TransformPanel : public IPanel
{
public:
	TransformPanel(const std::string& name, Repository* model, Canvas* canvas);
};

	}
}