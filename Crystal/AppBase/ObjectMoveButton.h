#pragma once

#include "IPopupButton.h"
#include "ObjectSelectButton.h"

namespace Crystal {
	namespace UI {

class ObjectMoveButton : public IPopupButton
{
public:
	ObjectMoveButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		objectButton("ObjectMove", model, canvas)
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