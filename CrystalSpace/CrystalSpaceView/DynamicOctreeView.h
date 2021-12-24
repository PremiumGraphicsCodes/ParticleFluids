#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class DynamicOctreeView : public IOkCancelView
{
public:
	DynamicOctreeView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

};

	}
}