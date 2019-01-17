#pragma once

#include "IPanel.h"

namespace Crystal {
	namespace UI {

class ParticlePanel : public IPanel
{
public:
	ParticlePanel(Model* model, ICanvas* canvas) :
		IPanel(model, canvas)
	{}

	void show() override;
};

	}
}