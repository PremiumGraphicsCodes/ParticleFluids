#pragma once

#include "IPopupButton.h"
#include "IntView.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFSphereButton : public IPopupButton
{
public:
	WFSphereButton(Repository* repository, Canvas* canvas) :
		IPopupButton("WFSphere", repository, canvas),
		sphere("Sphere"),
		attribute("Attribute"),
		unum("UNum", 12),
		vnum("VNum", 12)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	IntView unum;
	IntView vnum;
	Sphere3dView sphere;
	WFAttributeView attribute;
};

	}
}