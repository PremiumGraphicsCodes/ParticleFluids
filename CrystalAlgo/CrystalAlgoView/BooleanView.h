#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"

namespace Crystal {
	namespace UI {

class BooleanView : public IOkCancelView
{
public:
	BooleanView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	ObjectSelectView objectButton1;
	ObjectSelectView objectButton2;
};

	}
}