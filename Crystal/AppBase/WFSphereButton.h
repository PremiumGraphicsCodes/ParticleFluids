#pragma once

#include "IPopupButton.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFSphereButton : public IPopupButton
{
public:
	WFSphereButton(Repository* repository, Canvas* canvas) :
		IPopupButton("WFSphere", repository, canvas),
		sphereButton("Sphere"),
		attributeButton("Attribute"),
		unum(12),
		vnum(12)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	int unum;
	int vnum;
	Sphere3dView sphereButton;
	WFAttributeView attributeButton;
};

	}
}