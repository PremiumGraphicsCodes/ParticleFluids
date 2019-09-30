#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "Sphere3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFSphereView : public IWFAddView
{
public:
	WFSphereView(Scene::World* repository, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unum;
	IntView vnum;
	Sphere3dView sphere;
};

	}
}