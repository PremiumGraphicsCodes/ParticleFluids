#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
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
	ObjectSelectView mesh1;
	ObjectSelectView mesh2;
	DoubleView tolerance;
};

	}
}