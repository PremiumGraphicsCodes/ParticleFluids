#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

class WFBoxButton : public IPopupButton
{
public:
	WFBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("Box", model, canvas)
	{

	}

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	glm::vec3 min = { -1.0f, -1.0f, -1.0f };
	glm::vec3 max = { 1.0f, 1.0f, 1.0f };
	glm::vec4 color;
};


	}
}

