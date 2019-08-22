#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/DoubleView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VolumeConvertView : public IOkCancelView
{
public:
	VolumeConvertView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	ObjectSelectView objectButton;
	DoubleView searchRadius;
};

	}
}