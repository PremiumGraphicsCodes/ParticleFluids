#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ParticlePanel : public IPanel
{
public:
	ParticlePanel(Model* model, Canvas* canvas);

	void show() override;

};

	}
}