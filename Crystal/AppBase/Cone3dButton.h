#pragma once

#include "IPopupButton.h"

#include "../Math/Vector3d.h"
#include "../Math/Cone3d.h"

namespace Crystal {
	namespace UI {

class Cone3dButton : public IPopupButton
{
public:
	Cone3dButton(Repository* model, Canvas* canvas) :
		IPopupButton("Cone", model, canvas)
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

	Math::Cone3d getValue() const { return Math::Cone3d(center, radius, height); }

private:
	Math::Vector3df center = { 0.0, 0.0, 0.0 };
	double radius = 1.0;
	double height = 1.0;
};

	}
}
