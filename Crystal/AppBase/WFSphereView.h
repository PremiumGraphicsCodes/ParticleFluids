#pragma once

#include "IPanel.h"
#include "IntView.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFSphereView : public IPanel
{
public:
	WFSphereView(Repository* repository, Canvas* canvas) :
		IPanel("WFSphere", repository, canvas),
		sphere("Sphere"),
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
	Sphere3dView sphere;
	WFAttributeView attribute;
};

	}
}