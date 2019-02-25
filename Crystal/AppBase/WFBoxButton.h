#pragma once

#include "IPopupButton.h"
#include "Box3dButton.h"

namespace Crystal {
	namespace UI {

class WFBoxButton : public IPopupButton
{
public:
	WFBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("Box", model, canvas),
		boxButton("Box", model, canvas)
	{

	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Box3dButton boxButton;
	glm::vec4 color;
};


	}
}

