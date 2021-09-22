#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class ZOrderSearchView : public IOkCancelView
{
public:
	ZOrderSearchView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView searchRadius;
};

	}
}