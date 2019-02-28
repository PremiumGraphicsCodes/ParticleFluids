#pragma once

#include "IPopupButton.h"

#include "../Math/Vector3d.h"
#include "Torus3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFTorusButton : public IPopupButton
{
public:
	WFTorusButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFTorus", model, canvas),
		torus("Torus"),
		attribute("Attribute"),
		unum(24),
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
	TorusView torus;
	WFAttributeView attribute;
};

	}
}