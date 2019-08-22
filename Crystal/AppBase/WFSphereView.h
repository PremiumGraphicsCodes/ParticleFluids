#pragma once

#include "IOkCancelView.h"
#include "IntView.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFSphereView : public IOkCancelView
{
public:
	WFSphereView(Scene::World* repository, Canvas* canvas);

private:
	void onShow() override;

	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Sphere3dView sphere;
	WFAttributeView attribute;
};

	}
}