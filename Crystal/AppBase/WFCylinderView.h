#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "Cylinder3dView.h"

namespace Crystal {
	namespace UI {

class WFCylinderView : public IWFAddView
{
public:
	WFCylinderView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Cylinder3dView cylinder;
};

	}
}