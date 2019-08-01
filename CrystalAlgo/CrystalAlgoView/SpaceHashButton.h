#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"
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
	PositionSelectView positionButton;
	DoubleView searchRadius;
	ObjectSelectView objectButton;
};

	}
}