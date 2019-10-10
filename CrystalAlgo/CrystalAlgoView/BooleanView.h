#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/PositionSelectView.h"

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