#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/FloatView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

#include "../CrystalPhysics/KFFluidSolver.h"
#include "CSGBoundaryView.h"
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
	Physics::CSGBoundaryScene* csgScene;
	Physics::KFFluidSolver simulator;
	Physics::KFFUpdater updator;
	CSGBoundaryView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView timeStepView;
	FloatView radiusView;
	Button startButton;
	Button resetButton;
	int newId;

	std::unique_ptr<Shape::PolygonMesh> mesh;
};

	}
}