#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/FloatView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/ComboBox.h"

#include "../CrystalPhysics/SPHFlame/SPHFlameParticle.h"
#include "../CrystalPhysics/SPHFlame/SPHFlameSolver.h"
#include "../CrystalPhysics/SPHFlame/SPHFlameScene.h"


namespace Crystal {
	namespace UI {

class SPHFlameSimulationView : public IOkCancelView
{
public:
	SPHFlameSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::SPHFlameScene* flame;
	Physics::SPHFlameScene* heatSource;
	Physics::SPHFlameSolver* solver;
	Button startButton;
	Button resetButton;
	FloatView pressureCoeView;
	FloatView viscosityView;
	FloatView timeStepView;
	FloatView densityView;
	Box3dView boundaryView;
	ComboBox presenterView;
};

	}
}