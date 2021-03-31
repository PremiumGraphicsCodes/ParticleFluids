#pragma once

#include "IWFAddView.h"
#include "IntView.h"
//#include "Ellipsoid3dView.h"
#include "WFAttributeView.h"

namespace Crystal {
	namespace UI {

class WFEllipsoidView : public IWFAddView
{
public:
	WFEllipsoidView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unumView;
	IntView vnumView;
	//Sphere3dView sphereView;
};

	}
}