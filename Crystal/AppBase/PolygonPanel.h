#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class PolygonPanel : public IPanel
{
public:
	PolygonPanel(const std::string& name, Repository* model, Canvas* canvas);
};
	}
}