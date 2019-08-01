#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"

namespace Crystal {
	namespace UI {

class OctreeButton : public IPopupButton
{
public:
	OctreeButton(Scene::RootScene* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	PositionSelectView positionButton;
	ObjectSelectView objectButton;
};

	}
}