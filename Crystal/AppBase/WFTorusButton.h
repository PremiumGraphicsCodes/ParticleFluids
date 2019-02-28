#pragma once

#include "IPopupButton.h"

#include "../Math/Vector3d.h"
#include "Torus3dView.h"
#include "WFAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class WFTorusButton : public IPopupButton
{
public:
	WFTorusButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFTorus", model, canvas),
		torus("Torus"),
		attribute("Attribute"),
		unum("UNum", 24),
		vnum("VNum",12)
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
	TorusView torus;
	WFAttributeView attribute;
};

	}
}