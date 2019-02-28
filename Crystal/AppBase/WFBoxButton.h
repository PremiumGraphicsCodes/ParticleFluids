#pragma once

#include "IPopupButton.h"
#include "Box3dButton.h"
#include "WFAttributeButton.h"

namespace Crystal {
	namespace UI {

class WFBoxButton : public IPopupButton
{
public:
	WFBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("Box", model, canvas),
		boxButton("Box", model, canvas),
		attributeButton(model, canvas)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Box3dButton boxButton;
	WFAttributeButton attributeButton;
};


	}
}

