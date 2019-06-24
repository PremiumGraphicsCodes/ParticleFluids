#pragma once

#include "IPopupButton.h"

#include "Box3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "BoolView.h"

namespace Crystal {
	namespace UI {

class PSBoxButton : public IPopupButton
{
public:
	PSBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSBox", model, canvas),
		box("Box"),
		attribute("Attribute"),
		count("Count", 10000),
		isVolume("Volume", false)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Box3dView box;
	PSAttributeView attribute;
	IntView count;
	BoolView isVolume;
};

	}
}