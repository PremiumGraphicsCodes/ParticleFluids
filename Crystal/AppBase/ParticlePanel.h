#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ParticlePanel : public IPanel
{
public:
	ParticlePanel(const std::string& name, Model* model, Canvas* canvas);

};

	}
}