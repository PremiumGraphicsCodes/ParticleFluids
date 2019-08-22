#pragma once

#include "IOkCancelView.h"
#include "IntView.h"
#include "Cylinder3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFCylinderView : public IOkCancelView
{
public:
	WFCylinderView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Cylinder3dView cylinder;
	WFAttributeView attribute;
};

	}
}