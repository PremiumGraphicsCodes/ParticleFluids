#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "WFAttributeView.h"

#include "Cone3dView.h"

namespace Crystal {
	namespace UI {

class WFConeView : public IWFAddView
{
public:
	WFConeView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Cone3dView cone;
};

	}
}
