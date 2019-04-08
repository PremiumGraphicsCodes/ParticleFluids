#pragma once

#include "IPopupButton.h"
#include "Ray3dView.h"
#include "DoubleView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFRayButton : public IPopupButton
{
public:
	WFRayButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFRay", model, canvas),
		ray("Ray"),
		length("Length", 1.0),
		attribute("Attribute")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Ray3dView ray;
	DoubleView length;
	WFAttributeView attribute;
};


	}
}

