#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/DoubleView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VolumeConvertButton : public IPopupButton
{
public:
	VolumeConvertButton(Scene::RootScene* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	ObjectSelectView objectButton;
	DoubleView searchRadius;
};

	}
}