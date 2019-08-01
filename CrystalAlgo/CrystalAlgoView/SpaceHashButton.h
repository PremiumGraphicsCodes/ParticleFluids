#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"
#include "../../Crystal/AppBase/PositionSelectButton.h"
#include "../../Crystal/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class SpaceHashButton : public IPopupButton
{
public:
	SpaceHashButton(Scene::RootScene* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	PositionSelectButton positionButton;
	DoubleView searchRadius;
	ObjectSelectButton objectButton;
};

	}
}