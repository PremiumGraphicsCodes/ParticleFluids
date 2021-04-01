#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/FloatView.h"
#include "../../CrystalViewer/AppBase/ColorMapView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class SPHSurfaceBuilderView : public IOkCancelView
{
public:
	SPHSurfaceBuilderView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	FloatView searchRadiusView;
	FloatView cellLengthView;
	ColorMapView colorMapView;
};

	}
}