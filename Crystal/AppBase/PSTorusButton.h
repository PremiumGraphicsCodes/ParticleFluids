#pragma once

#include "IPopupButton.h"

#include "Torus3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSTorusButton : public IPopupButton
{
public:
	PSTorusButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSTorus", model, canvas),
		torusView("Torus"),
		attribute("Attribute"),
		count("Count", 10000)
	{
	}

	void onShow() override
	{
		torusView.show();
		attribute.show();
		count.show();
	}

	void onOk() override;

	void onCancel() override{}

private:
	TorusView torusView;
	PSAttributeView attribute;
	IntView count;
};

	}
}