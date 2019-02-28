#pragma once

#include "IPopupButton.h"

#include "Cone3dView.h"

namespace Crystal {
	namespace UI {

class PSConeButton : public IPopupButton
{
public:
	PSConeButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSCone", model, canvas),
		cone("Cone")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{
	}

private:
	Cone3dView cone;
	float size = 1.0f;
	int count = 10000;
};

	}
}
