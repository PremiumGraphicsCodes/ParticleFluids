#pragma once

#include "IPopupButton.h"
#include "Sphere3dButton.h"

namespace Crystal {
	namespace UI {

class PSSphereButton : public IPopupButton
{
public:
	PSSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("Sphere", model, canvas),
		sphereButton("Sphere", model, canvas)
	{

	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{
	}

private:
	Sphere3dButton sphereButton;
	float size = 1.0f;

	int count = 10000;
};

	}
}