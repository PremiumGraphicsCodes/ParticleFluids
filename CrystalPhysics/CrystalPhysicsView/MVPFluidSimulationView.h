#pragma once

#include "../../CrystalViewer/AppBase/IOkCancelView.h"
#include "../../CrystalViewer/AppBase/ObjectSelectView.h"
#include "../../CrystalViewer/AppBase/Box3dView.h"
#include "../../CrystalViewer/AppBase/FloatView.h"
#include "../../CrystalViewer/AppBase/DirectoryView.h"

#include "../CrystalPhysics/MVP/KFFluidSolver.h"
#include "CSGBoundaryView.h"
//#include "../CrystalPhysics/TimeSeriesParticleSystemWriter.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
		class KFFluidEmitterScene;
	}
	namespace UI {

class MVPFluidSimulationView : public IView
{
public:
	MVPFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	void onAddFluid();

	void onAddEmitter();

	void onStart();
	//void reset();

private:
	Physics::KFFluidScene* fluidScene;
	Physics::KFFluidScene* boundaryScene;
	Physics::KFFluidEmitterScene* emitterScene;
	Physics::CSGBoundaryScene* csgScene;
	Physics::KFFluidSolver solver;
	Physics::KFFUpdater updator;
	CSGBoundaryView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView timeStepView;
	FloatView radiusView;
	Button addFluidButton;
	Button addEmitterButton;
	Button startButton;
	//Button resetButton;
	int newId;

	std::unique_ptr<Shape::PolygonMesh> mesh;

	Scene::World* world;
	Canvas* canvas;
};

	}
}