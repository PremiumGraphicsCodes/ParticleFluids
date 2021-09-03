#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class LinearOctreeView : public IOkCancelView
{
public:
	LinearOctreeView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

};

	}
}