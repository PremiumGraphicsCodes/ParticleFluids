#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"

namespace Crystal {
	namespace UI {

class BooleanView : public IOkCancelView
{
public:
	BooleanView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void onOk() override;

private:
	ObjectSelectView objectButton1;
	ObjectSelectView objectButton2;
};

	}
}