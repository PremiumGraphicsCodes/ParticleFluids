#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

class PSSphereButton : public IPopupButton
{
public:
	PSSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("Sphere", model, canvas)
	{

	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{
	}

private:
	glm::vec3 center = { 0.0f, 0.0f, 0.0f };
	float radius = 1.0f;
	float size = 1.0f;

	int count = 10000;
};

	}
}