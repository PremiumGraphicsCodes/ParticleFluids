#pragma once

#include "IPopupButton.h"
#include "Box3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFBoxButton : public IPopupButton
{
public:
	WFBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("WFBox", model, canvas),
		boxButton("Box"),
		attributeButton("Attribute")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Box3dView boxButton;
	WFAttributeView attributeButton;
};


	}
}

