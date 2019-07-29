#pragma once

#include "IPanel.h"
#include "IntView.h"
#include "Cylinder3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFCylinderView : public IPanel
{
public:
	WFCylinderView(Repository* model, Canvas* canvas) :
		IPanel("WFCylinder", model, canvas),
		cylinder("Cylinder"),
		attribute("Attribute"),
		unum("UNum",12),
		vnum("VNum",12)
	{
	}

	void show() override;

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	Cylinder3dView cylinder;
	WFAttributeView attribute;
};

	}
}