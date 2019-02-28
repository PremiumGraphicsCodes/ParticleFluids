#pragma once

#include "IPopupButton.h"

#include "../Math/Vector3d.h"
#include "WFAttributeButton.h"

namespace Crystal {
	namespace UI {

class WFTorusButton : public IPopupButton
{
public:
	WFTorusButton(Repository* model, Canvas* canvas) :
		IPopupButton("Torus", model, canvas),
		attributeButton(model, canvas),
		unum(24),
		vnum(12)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	int unum;
	int vnum;
	Math::Vector3df center = { 0.0, 0.0, 0.0 };
	double bigRadius = 1.0;
	double smallRadius = 0.1;
	WFAttributeButton attributeButton;
};

	}
}