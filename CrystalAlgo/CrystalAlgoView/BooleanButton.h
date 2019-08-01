#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"
#include "../../Crystal/AppBase/PositionSelectButton.h"

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
	ObjectSelectButton objectButton1;
	ObjectSelectButton objectButton2;
};

	}
}