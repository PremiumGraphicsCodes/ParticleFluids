#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"
#include "../../Crystal/AppBase/PositionSelectView.h"

namespace Crystal {
	namespace UI {

class OctreeView : public IOkCancelView
{
public:
	OctreeView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void onOk() override;

private:
	PositionSelectView positionButton;
	ObjectSelectView objectButton;
};

	}
}