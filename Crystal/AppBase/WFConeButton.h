#pragma once

#include "IPopupButton.h"
#include "WFAttributeView.h"

#include "../Math/Vector3d.h"
#include "Cone3dView.h"

namespace Crystal {
	namespace UI {

class WFConeButton : public IPopupButton
{
public:
	WFConeButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFCone", model, canvas),
		coneButton("Cone"),
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
	Cone3dView coneButton;
	WFAttributeView attributeButton;
};

	}
}
