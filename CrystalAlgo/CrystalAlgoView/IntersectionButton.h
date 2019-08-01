#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"
#include "../../Crystal/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class IntersectionButton : public IPopupButton
{
public:
	IntersectionButton(Scene::RootScene* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	ObjectSelectButton mesh1;
	ObjectSelectButton mesh2;
	DoubleView tolerance;
};

	}
}