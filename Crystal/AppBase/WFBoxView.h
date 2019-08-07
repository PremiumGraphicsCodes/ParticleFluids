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

	void show() override;

private:
	void onOk() override;

private:
	Box3dView box;
	WFAttributeView attribute;
};


	}
}

