#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/PositionSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class ZOrderSearchView : public IOkCancelView
{
public:
	ZOrderSearchView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	PositionSelectView positionButton;
	DoubleView searchRadius;
	ObjectSelectView objectButton;
};

	}
}