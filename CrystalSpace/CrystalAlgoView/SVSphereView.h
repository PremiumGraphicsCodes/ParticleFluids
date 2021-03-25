#pragma once

#include "ISVAddView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"

namespace Crystal {
	namespace UI {

class SVSphereView : public ISVAddView
{
public:
	SVSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Box3dView boxView;
	IntView resolutionView;
};

	}
}