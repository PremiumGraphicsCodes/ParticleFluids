#pragma once

#include "../../Crystal/AppBase/IPopupButton.h"
#include "../../Crystal/AppBase/Box3dView.h"
#include "../../Crystal/AppBase/ObjectSelectButton.h"

namespace Crystal {
	namespace UI {

class VolumeButton : public IPopupButton
{
public:
	VolumeButton(Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	Box3dView box;
};

	}
}