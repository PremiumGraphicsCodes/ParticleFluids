#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"
#include "../../Crystal/AppBase/DoubleView.h"

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
	std::array< DoubleView, 8 > values;
};

	}
}