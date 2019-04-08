#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/Plane3dView.h"
#include "../../Crystal/AppBase/Ray3dView.h"
#include "../../Crystal/AppBase/DoubleView.h"

namespace Crystal {
	namespace UI {

class IntersectionButton : public IPopupButton
{
public:
	IntersectionButton(Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Ray3dView ray;
	Plane3dView plane;
	DoubleView tolerance;
};

	}
}