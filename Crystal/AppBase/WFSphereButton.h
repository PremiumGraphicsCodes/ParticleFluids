#pragma once

#include "IPopupButton.h"
#include "Sphere3dButton.h"

namespace Crystal {
	namespace UI {

class WFSphereButton : public IPopupButton
{
public:
	WFSphereButton(Repository* repository, Canvas* canvas) :
		IPopupButton("Sphere", repository, canvas),
		sphereButton("Sphere", repository, canvas),
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
	Sphere3dButton sphereButton;
	glm::vec4 color;
};

	}
}