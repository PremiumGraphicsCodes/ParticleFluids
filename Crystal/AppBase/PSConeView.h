#pragma once

#include "IPopupButton.h"

#include "Cone3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSConeView : public IPanel
{
public:
	PSConeView(Repository* model, Canvas* canvas);

	void show() override;

	void onOk();

private:
	Cone3dView cone;
	PSAttributeView attribute;
	IntView count;
	Button okButton;
};

	}
}
