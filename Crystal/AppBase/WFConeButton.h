#pragma once

#include "IPopupButton.h"
#include "WFAttributeButton.h"

#include "../Math/Vector3d.h"
#include "Cone3dButton.h"

namespace Crystal {
	namespace UI {

class WFConeButton : public IPopupButton
{
public:
	WFConeButton(Repository* model, Canvas* canvas) :
		IPopupButton("Cone", model, canvas),
		coneButton(model, canvas),
		attributeButton("Attribute", model, canvas),
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
	Cone3dButton coneButton;
	WFAttributeButton attributeButton;
};

	}
}
