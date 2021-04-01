#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/Sphere3dView.h"
#include "../../CrystalViewer/AppBase/IntView.h"

namespace Crystal {
	namespace UI {

class ToVDBVolumeView : public IOkCancelView
{
public:
	ToVDBVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Sphere3dView sphereView;
	IntView resolutionView;
	//ObjectSelectView particleSystemSelectView;
	//DoubleView radiusView;
};

	}
}