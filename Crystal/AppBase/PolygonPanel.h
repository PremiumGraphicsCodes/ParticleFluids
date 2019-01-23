#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class PolygonPanel : public IPanel
{
public:
	PolygonPanel(Model* model, Canvas* canvas);

	void show() override;
};
	}
}