#pragma once

#include "IPanel.h"
#include "IntView.h"
#include "WFAttributeView.h"

#include "../Math/Vector3d.h"
#include "Cone3dView.h"

namespace Crystal {
	namespace UI {

class WFConeView : public IPanel
{
public:
	WFConeView(Repository* model, Canvas* canvas) :
		IPanel("WFCone", model, canvas),
		cone("Cone"),
		attribute("Attribute"),
		unum("UNum", 12),
		vnum("VNum", 12)
	{
	}

	void show() override;

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	Cone3dView cone;
	WFAttributeView attribute;
};

	}
}
