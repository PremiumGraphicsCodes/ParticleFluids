#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/FloatView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"
#include "../CrystalPhysics/CSPH/CSPHSolver.h"
#include "../CrystalPhysics/CSPH/CSPHFluidScene.h"

namespace Crystal {
	namespace UI {

class CSPHFluidSimulationView : public IOkCancelView
{
public:
	CSPHFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::CSPHFluidScene* fluidScene;
	Physics::CSPHSolver* simulator;
	Button startButton;
	Button resetButton;
	//Button nextButton;
	FloatView pressureCoeView;
	FloatView viscosityView;
	FloatView timeStepView;
	FloatView densityView;
	Box3dView boundaryView;
	DirectoryView outputDirectoryView;
	int newId;
};

	}
}