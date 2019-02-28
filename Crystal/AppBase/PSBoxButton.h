#pragma once

#include "IPopupButton.h"

#include "Box3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSBoxButton : public IPopupButton
{
public:
	PSBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSBox", model, canvas),
		box("Box"),
		count("Count", 10000)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Box3dView box;
	IntView count;
};

	}
}