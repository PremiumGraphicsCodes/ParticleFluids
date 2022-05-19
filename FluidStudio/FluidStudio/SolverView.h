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
#include "SolverModel.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;
		class MVPFluidEmitterScene;
	}
}

namespace PG {
	namespace FS {
		class SolverExporter;

class SolverView : public Crystal::UI::IView
{
public:
	SolverView(const std::string& name, Crystal::Scene::World* world, Crystal::UI::Canvas* canvas, SolverModel* model);

private:

	void onStart();

	void onReset();

private:
	Crystal::UI::Box3dView boundaryView;
	Crystal::UI::FloatView timeStepView;
	Crystal::UI::FloatView radiusView;
	Crystal::UI::Vector3dView externalForceView;
	Crystal::UI::Vector3dView buoyancyView;
	Crystal::UI::Button startButton;
	Crystal::UI::Button resetButton;
	int newId;

	Crystal::Scene::World* world;
	Crystal::UI::Canvas* canvas;

	Crystal::UI::BoolView doExportView;
	Crystal::UI::DirectoryView exportDirecotryView;
	Crystal::UI::IntView exportIntervalView;
	PG::FS::SolverModel* model;
};

	}
}