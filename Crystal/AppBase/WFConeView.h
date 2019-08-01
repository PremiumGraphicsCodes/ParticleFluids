#pragma once

#include "IPanel.h"
#include "IntView.h"
#include "WFAttributeView.h"

#include "../Math/Vector3d.h"
#include "Cone3dView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class WFConeView : public IPanel
{
public:
	WFConeView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	Cone3dView cone;
	WFAttributeView attribute;
	Button ok;
};

	}
}
