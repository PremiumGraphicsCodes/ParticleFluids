#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class SceneGenerationPanel : public IPanel
{
public:
	SceneGenerationPanel(const std::string& name, Repository* model, Canvas* canvas);
};

	}
}