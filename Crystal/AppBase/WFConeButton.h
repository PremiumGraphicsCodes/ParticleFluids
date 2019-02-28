#pragma once

#include "IPopupButton.h"
#include "IntView.h"
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
		cone("Cone"),
		attribute("Attribute"),
		unum("UNum", 12),
		vnum("VNum", 12)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	IntView unum;
	IntView vnum;
	Cone3dView cone;
	WFAttributeView attribute;
};

	}
}
