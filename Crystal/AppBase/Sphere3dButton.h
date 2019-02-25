#pragma once

#include "IPopupButton.h"
#include "../Math/Sphere3d.h"

namespace Crystal {
	namespace UI {

class Sphere3dButton : public IPopupButton
{
public:
	Sphere3dButton(const std::string& name, Repository* repository, Canvas* canvas) :
		IPopupButton(name, repository, canvas)
	{}

	void onShow() override;

	void onOk() override{}

	void onCancel() override {}

	Math::Sphere3d getValue() const { return Math::Sphere3d(center, radius); }

private:
	glm::vec3 center = { 0.0f, 0.0f, 0.0f };
	double radius = 1.0;
};
	}
}

