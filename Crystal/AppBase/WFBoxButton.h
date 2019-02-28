#pragma once

#include "IPopupButton.h"
#include "Box3dView.h"
#include "WFAttributeButton.h"

namespace Crystal {
	namespace UI {

class WFBoxButton : public IPopupButton
{
public:
	WFBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFBox", model, canvas),
		boxButton("Box"),
		attributeButton("Attribute",model, canvas)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Box3dView boxButton;
	WFAttributeButton attributeButton;
};


	}
}

