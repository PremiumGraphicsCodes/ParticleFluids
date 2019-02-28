#pragma once

#include "IPopupButton.h"
#include "Cylinder3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFCylinderButton : public IPopupButton
{
public:
	WFCylinderButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFCylinder", model, canvas),
		cylinder("Cylinder"),
		attribute("Attribute"),
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
	Cylinder3dView cylinder;
	WFAttributeView attribute;
};

	}
}