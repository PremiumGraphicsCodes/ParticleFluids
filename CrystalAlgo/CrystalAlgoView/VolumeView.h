#pragma once

#include "../../Crystal/AppBase/IOkCancelView.h"
#include "../../Crystal/AppBase/Box3dView.h"

namespace Crystal {
	namespace UI {

class VolumeView : public IOkCancelView
{
public:
	VolumeView(Scene::World* model, Canvas* canvas);

	void show() override;

	void onOk() override;

private:
	Box3dView box;
};

	}
}