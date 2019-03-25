#pragma once

#include "IPopupButton.h"

#include "Vector3dView.h"
#include "PMAttributeView.h"

namespace Crystal {
	namespace UI {

class PMPlaneButton : public IPopupButton
{
public:
	PMPlaneButton(Repository* model, Canvas* canvas);

	void onShow();

	void onOk();

	void onCancel()
	{

	}

private:
	Vector3dView originView;
	Vector3dView uvecView;
	Vector3dView vvecView;
	PMAttributeView attribute;
};

	}
}
