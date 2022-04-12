#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class ToVDBVolumeView : public IOkCancelView
{
public:
	ToVDBVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView scaleView;
};

	}
}