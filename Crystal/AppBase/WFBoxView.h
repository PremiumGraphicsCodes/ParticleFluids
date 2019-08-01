#pragma once

#include "IPanel.h"
#include "Box3dView.h"
#include "WFAttributeView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class WFBoxView : public IPanel
{
public:
	WFBoxView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Box3dView box;
	WFAttributeView attribute;
	Button ok;
};


	}
}

