#pragma once

#include "IPanel.h"
#include "IntView.h"
#include "Cylinder3dView.h"
#include "WFAttributeView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class WFCylinderView : public IPanel
{
public:
	WFCylinderView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	Cylinder3dView cylinder;
	WFAttributeView attribute;
	Button ok;
};

	}
}