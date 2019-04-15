#pragma once

#include "IPopupButton.h"
#include "ObjectSelectButton.h"

namespace Crystal {
	namespace UI {

class ScaleButton : public IPopupButton
{
public:
	ScaleButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		objectButton("Object", model, canvas)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override { }

private:
	ObjectSelectButton objectButton;
};

	}
}