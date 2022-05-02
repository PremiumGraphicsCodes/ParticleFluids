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
	//void onAddFluid();

	//void onAddEmitter();

	void onStart();

	void onReset();

private:
	void addFluid();

	void addEmitter();

	Box3dView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView heatDiffuseCoeView;
	FloatView dragHeatCoeView;
	FloatView dragForceCoeView;
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
	SolverExporter* exporter;
	MainModel* model;
};

	}
}