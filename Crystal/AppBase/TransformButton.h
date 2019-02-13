#pragma once

#include "IPopupButton.h"
#include "ObjectSelectButton.h"

namespace Crystal {
	namespace UI {

class TransformButton : public IPopupButton
{
public:
	TransformButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		objectButton("Transform", model, canvas)
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