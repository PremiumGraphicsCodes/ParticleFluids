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
	WFSphereView(Scene::RootScene* repository, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Sphere3dView sphere;
	WFAttributeView attribute;
};

	}
}