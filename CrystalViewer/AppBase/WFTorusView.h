#pragma once

#include "IWFAddView.h"

#include "Torus3dView.h"
#include "WFAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class WFTorusView : public IWFAddView
{
public:
	WFTorusView(Scene::World* model, Canvas* canvas);

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	TorusView torus;
};

	}
}