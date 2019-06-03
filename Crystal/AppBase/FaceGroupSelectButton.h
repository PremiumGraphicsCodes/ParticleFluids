#pragma once

#include "IPopupButton.h"
#include "FaceGroupView.h"

namespace Crystal {
	namespace UI {

class FaceGroupSelectButton : public IPopupButton
{
public:
	FaceGroupSelectButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		group("SelectedGroup")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	FaceGroupView group;
};

	}
}