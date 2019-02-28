#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class PolygonMeshPanel : public IPanel
{
public:
	PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas);
};
	}
}