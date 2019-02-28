#pragma once

#include "IPopupButton.h"
#include "WFAttributeButton.h"

namespace Crystal {
	namespace UI {

class WFCylinderButton : public IPopupButton
{
public:
	WFCylinderButton(Repository* model, Canvas* canvas) :
		IPopupButton("Cylinder", model, canvas),
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
	glm::vec3 center = { 0.0f, 0.0f, 0.0f };
	double radius = 1.0;
	double height = 1.0;
	WFAttributeButton attributeButton;
};

	}
}