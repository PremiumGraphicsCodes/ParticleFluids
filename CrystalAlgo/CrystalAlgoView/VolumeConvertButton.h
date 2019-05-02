#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/DoubleView.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"

namespace Crystal {
	namespace UI {

class VolumeConvertButton : public IPopupButton
{
public:
	VolumeConvertButton(Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	ObjectSelectButton objectButton;
	DoubleView searchRadius;
};

	}
}