#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ParticlePanel : public IPanel
{
public:
	ParticlePanel(const std::string& name, Repository* model, Canvas* canvas);

};

	}
}