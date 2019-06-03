#pragma once

#include "IPopupButton.h"
#include "FaceView.h"

namespace Crystal {
	namespace UI {

class FaceSelectButton : public IPopupButton
{
public:
	FaceSelectButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		face("SelectedFace")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	FaceView face;
};

	}
}