#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"

namespace Crystal {
	namespace UI {

class VolumeView : public IOkCancelView
{
public:
	VolumeView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	Box3dView box;
};

	}
}