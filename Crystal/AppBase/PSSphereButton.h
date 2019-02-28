#pragma once

#include "IPopupButton.h"
#include "Sphere3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSSphereButton : public IPopupButton
{
public:
	PSSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSSphere", model, canvas),
		sphere("Sphere"),
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
	Sphere3dView sphere;
	PSAttributeView attribute;
	IntView count;
};

	}
}