#pragma once

#include "IOkCancelView.h"
#include "IntView.h"
#include "WFAttributeView.h"

#include "Cone3dView.h"

namespace Crystal {
	namespace UI {

class WFConeView : public IOkCancelView
{
public:
	WFConeView(Scene::World* model, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Cone3dView cone;
	WFAttributeView attribute;
};

	}
}
