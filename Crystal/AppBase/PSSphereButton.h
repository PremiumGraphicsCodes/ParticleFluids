#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "IntView.h"
#include "Sphere3dView.h"

namespace Crystal {
	namespace UI {

class PSSphereButton : public IPopupButton
{
public:
	PSSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSSphere", model, canvas),
		sphere("Sphere"),
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
	Sphere3dView sphere;
	FloatView size;
	IntView count;
};

	}
}