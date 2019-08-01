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
	WFTorusView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

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