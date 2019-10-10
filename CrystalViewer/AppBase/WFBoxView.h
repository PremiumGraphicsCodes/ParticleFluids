#pragma once

#include "IWFAddView.h"
#include "Box3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFBoxView : public IWFAddView
{
public:
	WFBoxView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView box;
};


	}
}

