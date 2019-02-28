#pragma once

#include "IPopupButton.h"

#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class PSBoxButton : public IPopupButton
{
public:
	PSBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSBox", model, canvas),
		boxButton("Box")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Box3dView boxButton;
	int count = 10000;
};

	}
}