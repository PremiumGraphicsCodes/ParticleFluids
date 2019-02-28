#pragma once

#include "IPopupButton.h"

#include "Cone3dView.h"
#include "FloatView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSConeButton : public IPopupButton
{
public:
	PSConeButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSCone", model, canvas),
		cone("Cone"),
		size("Size", 1.0f),
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
	FloatView size;
	IntView count;
};

	}
}
