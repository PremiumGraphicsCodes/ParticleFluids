#pragma once

#include "IPopupButton.h"
#include "Cylinder3dButton.h"
#include "WFAttributeButton.h"

namespace Crystal {
	namespace UI {

class WFCylinderButton : public IPopupButton
{
public:
	WFCylinderButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFCylinder", model, canvas),
		cylinderButton(model, canvas),
		attributeButton("Attribute",model, canvas),
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
	Cylinder3dButton cylinderButton;
	WFAttributeButton attributeButton;
};

	}
}