#pragma once

#include "IPopupButton.h"

#include "Cone3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSConeButton : public IPopupButton
{
public:
	PSConeButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSCone", model, canvas),
		cone("Cone"),
		attribute("Attribute"),
		count("Count", 10000)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{
	}

private:
	Cone3dView cone;
	PSAttributeView attribute;
	IntView count;
};

	}
}
