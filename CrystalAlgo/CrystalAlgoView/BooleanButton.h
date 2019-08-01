#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"

namespace Crystal {
	namespace UI {

class BooleanButton : public IPopupButton
{
public:
	BooleanButton(Scene::RootScene* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	ObjectSelectView objectButton1;
	ObjectSelectView objectButton2;
};

	}
}