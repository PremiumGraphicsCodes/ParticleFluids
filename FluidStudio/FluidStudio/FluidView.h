#pragma once

#include "CrystalScene/AppBase/IView.h"
#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/FloatView.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"

namespace Crystal {
	namespace UI {

class FluidView : public IView
{
public:
	FluidView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void addFluid();

	void addEmitter();

	Physics::MVPFluidScene* fluidScene;
	Physics::MVPFluidScene* staticScene;
	Physics::MVPFluidEmitterScene* emitterScene;

	Box3dView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView heatDiffuseCoeView;
	FloatView dragHeatCoeView;
	FloatView dragForceCoeView;

};
	}
}