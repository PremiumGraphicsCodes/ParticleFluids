#pragma once

#include "IPopupButton.h"

#include "../Math/Cylinder3d.h"

namespace Crystal {
	namespace UI {

class Cylinder3dButton : public IPopupButton
{
public:
	Cylinder3dButton(Repository* model, Canvas* canvas) :
		IPopupButton("Cylinder", model, canvas),
		radius(1.0),
		height(1.0)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override{}

	Math::Cylinder3d getValue() const {
		return Math::Cylinder3d(radius, height, center);
	}

private:
	glm::vec3 center = { 0.0f, 0.0f, 0.0f };
	double radius = 1.0;
	double height = 1.0;
};

	}
}