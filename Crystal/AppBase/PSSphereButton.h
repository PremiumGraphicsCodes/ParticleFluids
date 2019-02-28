#pragma once

#include "IPopupButton.h"
#include "Sphere3dView.h"

namespace Crystal {
	namespace UI {

class PSSphereButton : public IPopupButton
{
public:
	PSSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSSphere", model, canvas),
		sphereButton("Sphere")
	{

	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{
	}

private:
	Sphere3dView sphereButton;
	float size = 1.0f;

	int count = 10000;
};

	}
}