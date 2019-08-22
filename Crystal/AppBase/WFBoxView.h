#pragma once

#include "IOkCancelView.h"
#include "Box3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFBoxView : public IOkCancelView
{
public:
	WFBoxView(Scene::World* model, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	Box3dView box;
	WFAttributeView attribute;
};


	}
}

