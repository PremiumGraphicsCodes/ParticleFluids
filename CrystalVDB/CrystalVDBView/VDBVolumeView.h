#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class VDBVolumeView : public IOkCancelView
{
public:
	VDBVolumeView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	DoubleView scaleView;
	//ObjectSelectView particleSystemSelectView;
};

	}
}