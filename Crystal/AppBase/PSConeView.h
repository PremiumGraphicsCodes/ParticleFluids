#pragma once

#include "IPopupButton.h"

#include "Cone3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "StringView.h"
#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSConeView : public IPanel
{
public:
	PSConeView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Cone3dView cone;
	PSAttributeView attribute;
	IntView count;
	StringView name;
	Button ok;
};

	}
}
