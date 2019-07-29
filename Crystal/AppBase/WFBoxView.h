#pragma once

#include "IPanel.h"
#include "Box3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFBoxView : public IPanel
{
public:
	WFBoxView(Repository* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Box3dView box;
	WFAttributeView attribute;
};


	}
}

