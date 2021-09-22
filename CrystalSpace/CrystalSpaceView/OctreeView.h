#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

class OctreeView : public IOkCancelView
{
public:
	OctreeView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

};

	}
}