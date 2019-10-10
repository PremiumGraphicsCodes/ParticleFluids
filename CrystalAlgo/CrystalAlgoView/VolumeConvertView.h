#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"

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