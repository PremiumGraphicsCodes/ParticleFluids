#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

class Box3dButton : public IPopupButton
{
public:
	Box3dButton(const std::string& name, Repository* repository, Canvas* canvas) :
		IPopupButton(name, repository, canvas)
	{
	}

	void onShow() override;

	void onOk() override {};

	void onCancel() override {};

	Math::Box3d getValue() const { return Math::Box3d(min, max); }

private:
	glm::vec3 min = { -1.0f, -1.0f, -1.0f };
	glm::vec3 max = { 1.0f, 1.0f, 1.0f };

};
	}
}