#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;
		class PBSPHSolver;
	}
	namespace UI {

class PBSPHFluidSimulationView : public IOkCancelView
{
public:
	PBSPHFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void onReset();

private:
	Physics::PBSPHSolver* simulator;
	Physics::PBFluidScene* fluidScene;
	Physics::PBFluidScene* boundaryScene;
	ObjectSelectView particleSystemSelectView;
	ObjectSelectView boundarySelectView;
	Button startButton;
	Button resetButton;
	DoubleView timeStepView;
	DoubleView radiusView;
	DoubleView effectLengthView;
	DoubleView densityView;
	DoubleView stiffnessView;
	DoubleView vicsocityView;
	Box3dView boundaryView;
};

	}
}