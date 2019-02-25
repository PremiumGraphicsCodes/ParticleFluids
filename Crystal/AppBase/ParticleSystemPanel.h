#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ParticleSystemPanel : public IPanel
{
public:
	ParticleSystemPanel(const std::string& name, Repository* model, Canvas* canvas);

};

	}
}