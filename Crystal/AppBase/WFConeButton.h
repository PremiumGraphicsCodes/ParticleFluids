#pragma once

#include "IPopupButton.h"
#include "WFAttributeButton.h"

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace UI {

class WFConeButton : public IPopupButton
{
public:
	WFConeButton(Repository* model, Canvas* canvas) :
		IPopupButton("Cone", model, canvas),
		attributeButton(model, canvas),
		unum(12),
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
	double radius = 1.0;
	double height = 1.0;
	WFAttributeButton attributeButton;
};

	}
}
