#pragma once

#include "IPopupButton.h"
#include "../Math/Sphere3d.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Sphere3dButton : public IPopupButton
{
public:
	Sphere3dButton(const std::string& name, Repository* repository, Canvas* canvas) :
		IPopupButton(name, repository, canvas),
		radius("Radius", 1.0)
	{}

	void onShow() override;

	void onOk() override{}

	void onCancel() override {}

	Math::Sphere3d getValue() const { return Math::Sphere3d(center, radius.getValue()); }

private:
	glm::vec3 center = { 0.0f, 0.0f, 0.0f };
	DoubleView radius;
};
	}
}

