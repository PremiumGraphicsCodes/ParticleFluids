#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"

namespace Crystal {
	namespace UI {

class SpaceHashButton : public IPopupButton
{
public:
	SpaceHashButton(Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	glm::vec3 min = { -10.0f, -10.0f, -10.0f };
	glm::vec3 max = { 10.0f, 10.0f, 10.0f };
	glm::vec3 dx = { 1.0f, 1.0f, 1.0f };
};

	}
}