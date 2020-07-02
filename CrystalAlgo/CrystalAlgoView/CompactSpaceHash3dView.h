#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class CompactSpaceHash3dView : public IOkCancelView
{
public:
	CompactSpaceHash3dView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView searchRadius;
};

	}
}