#pragma once

#include "CrystalScene/AppBase/IView.h"
#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/FloatView.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "MainModel.h"

namespace Crystal {
	namespace UI {

class FluidView : public IOkCancelView
{
public:
	FluidView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(MVPFluidScene* fluid);

private:
	void onOk() override;

	MVPFluidScene* fluidScene;
	Box3dView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView heatDiffuseCoeView;
	FloatView dragHeatCoeView;
	FloatView dragForceCoeView;

};
	}
}