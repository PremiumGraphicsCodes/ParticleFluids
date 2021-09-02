#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"

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