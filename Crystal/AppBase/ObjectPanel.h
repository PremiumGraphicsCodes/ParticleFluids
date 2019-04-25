#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ObjectPanel : public IPanel
{
public:
	ObjectPanel(const std::string& name, Repository* model, Canvas* canvas);
};

	}
}