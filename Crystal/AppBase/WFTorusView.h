#pragma once

#include "IPanel.h"

#include "Torus3dView.h"
#include "WFAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class WFTorusView : public IPanel
{
public:
	WFTorusView(Scene::World* model, Canvas* canvas);

	void onShow() override;

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	TorusView torus;
	WFAttributeView attribute;
};

	}
}