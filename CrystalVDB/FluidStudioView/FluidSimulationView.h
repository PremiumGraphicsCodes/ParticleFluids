#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/DoubleView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

#include "../../CrystalAlgo/CrystalPhysics/KFFluidSolver.h"
#include "TimeSeriesParticleSystemWriter.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {

class FluidSimulationView : public IOkCancelView
{
public:
	FluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

	void reset();

private:
	Physics::KFFluidScene* fluidScene;
	Physics::KFFluidScene* boundaryScene;
	Physics::KFFluidSolver simulator;
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
	Physics::TimeSeriesParticleSystemWriter writer;
	DirectoryView outputDirectoryView;
};

	}
}