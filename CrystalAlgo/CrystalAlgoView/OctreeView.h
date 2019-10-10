#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/PositionSelectView.h"

namespace Crystal {
	namespace UI {

class OctreeView : public IOkCancelView
{
public:
	OctreeView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	PositionSelectView positionButton;
	ObjectSelectView objectButton;
};

	}
}