#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"

namespace Crystal {
	namespace UI {

class MarchingCubesButton : public IPopupButton
{
public:
	MarchingCubesButton(Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	ObjectSelectButton objectButton1;
};

	}
}