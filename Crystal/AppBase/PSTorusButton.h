#pragma once

#include "IPopupButton.h"

#include "Torus3dView.h"
#include "FloatView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSTorusButton : public IPopupButton
{
public:
	PSTorusButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSTorus", model, canvas),
		torusView("Torus"),
		sizeView("Size", 1.0f),
		count("Count", 10000)
	{
	}

	void onShow() override
	{
		torusView.show();
		sizeView.show();
		count.show();
	}

	void onOk() override;

	void onCancel() override
	{
	}

private:
	TorusView torusView;
	FloatView sizeView;
	IntView count;
};

	}
}