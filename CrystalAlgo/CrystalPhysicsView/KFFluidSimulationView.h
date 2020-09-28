#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

#include "../CrystalPhysics/KFFluidSolver.h"
//#include "../CrystalPhysics/TimeSeriesParticleSystemWriter.h"

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
	Physics::KFFluidScene* boundaryScene;
	Physics::KFFluidSolver simulator;
	Physics::KFFluidSolver::Args args;
	Box3dView boundaryView;
	DoubleView pressureCoeView;
	DoubleView viscosityCoeView;
	DoubleView timeStepView;
	Button startButton;
	Button resetButton;
	int newId;

	ObjectSelectView particleSystemSelectView;
	ObjectSelectView boundarySelectView;
	DoubleView radiusView;
	//Physics::TimeSeriesParticleSystemWriter writer;
	DirectoryView outputDirectoryView;
};

	}
}