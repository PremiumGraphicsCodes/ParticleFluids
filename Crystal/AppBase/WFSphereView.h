#pragma once

#include "IPanel.h"
#include "IntView.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class WFSphereView : public IPanel
{
public:
	WFSphereView(Repository* repository, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	IntView unum;
	IntView vnum;
	Sphere3dView sphere;
	WFAttributeView attribute;
	Button ok;
};

	}
}