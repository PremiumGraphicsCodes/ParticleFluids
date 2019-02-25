#pragma once

#include "IPopupButton.h"

#include "Box3dButton.h"

namespace Crystal {
	namespace UI {

class PSBoxButton : public IPopupButton
{
public:
	PSBoxButton(Repository* model, Canvas* canvas) :
		boxButton("Box", model, canvas),
		IPopupButton("Box", model, canvas)
	{

	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Box3dButton boxButton;
	int count = 10000;
};

	}
}