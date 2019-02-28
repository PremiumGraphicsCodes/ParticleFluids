#pragma once

#include "IPopupButton.h"
#include "Cylinder3dView.h"
#include "WFAttributeButton.h"

namespace Crystal {
	namespace UI {

class WFCylinderButton : public IPopupButton
{
public:
	WFCylinderButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFCylinder", model, canvas),
		cylinderButton("Cylinder"),
		attributeButton("Attribute"),
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
	Cylinder3dView cylinderButton;
	WFAttributeButton attributeButton;
};

	}
}