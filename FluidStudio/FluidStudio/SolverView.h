#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/FloatView.h"
#include "CrystalScene/AppBase/Vector3dView.h"
#include "CrystalScene/AppBase/BoolView.h"
#include "CrystalScene/AppBase/DirectoryView.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
//#include "CSGBoundaryView.h"
//#include "../CrystalPhysics/TimeSeriesParticleSystemWriter.h"
#include "MainModel.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;
		class MVPFluidEmitterScene;
	}
	namespace UI {
		class SolverExporter;

class SolverView : public IView
{
public:
	SolverView(const std::string& name, Scene::World* world, Canvas* canvas, MainModel* model);

private:
	//void onAddEmitter();

	void onStart();

	void onReset();

private:

	Box3dView boundaryView;
	FloatView timeStepView;
	FloatView radiusView;
	Vector3dView externalForceView;
	Vector3dView buoyancyView;
	Button startButton;
	Button resetButton;
	int newId;

	Scene::World* world;
	Canvas* canvas;

	BoolView doExportView;
	DirectoryView exportDirecotryView;
	IntView exportIntervalView;
	MainModel* model;
};

	}
}