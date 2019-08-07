#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"
#include "../../Crystal/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class SpaceHashView : public IOkCancelView
{
public:
	SpaceHashView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void onOk() override;

private:
	PositionSelectView positionButton;
	DoubleView searchRadius;
	ObjectSelectView objectButton;
};

	}
}