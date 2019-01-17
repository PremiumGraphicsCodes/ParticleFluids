#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ParticlePanel : public IPanel
{
public:
	ParticlePanel(Model* model, Canvas* canvas) :
		IPanel(model, canvas)
	{}

	void show() override;
};

	}
}