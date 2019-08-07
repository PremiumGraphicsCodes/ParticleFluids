#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/DoubleView.h"
#include "../../Crystal/AppBase/ObjectSelectView.h"

namespace Crystal {
	namespace UI {

class VolumeConvertView : public IOkCancelView
{
public:
	VolumeConvertView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

	void onOk() override;

private:
	ObjectSelectView objectButton;
	DoubleView searchRadius;
};

	}
}