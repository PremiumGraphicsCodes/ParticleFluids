#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"

#include "../CrystalPhysics/KFFluidSolver.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class KFFluidSimulationView : public IOkCancelView
{
public:
	KFFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
	Physics::KFFluidScene* fluidScene;
	Physics::KFFluidSolver simulator;
	Box3dView boundaryView;
	DoubleView pressureCoeView;
	DoubleView viscosityCoeView;
	DoubleView timeStepView;
	Button startButton;
	Button resetButton;
	int newId;

	ObjectSelectView particleSystemSelectView;
	DoubleView radiusView;
};

	}
}