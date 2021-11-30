#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/ObjectSelectView.h"
#include "CrystalScene/AppBase/Box3dView.h"
#include "CrystalScene/AppBase/FloatView.h"

#include "../CrystalPhysics/MVP/MVPFluidSolver.h"
#include "CSGBoundaryView.h"
//#include "../CrystalPhysics/TimeSeriesParticleSystemWriter.h"

namespace Crystal {
	namespace Physics {
		class MVPFluidScene;
		class MVPFluidEmitterScene;
	}
	namespace UI {

class MVPFluidSimulationView : public IView
{
public:
	MVPFluidSimulationView(Scene::World* model, Canvas* canvas);

private:
	//void onAddFluid();

	//void onAddEmitter();

	void onStart();

	void onReset();

private:
	void addFluid();

	void addEmitter();

	Physics::MVPFluidScene* fluidScene;
	Physics::MVPFluidScene* boundaryScene;
	Physics::MVPFluidEmitterScene* emitterScene;
	Physics::CSGBoundaryScene* csgScene;
	Scene::TriangleMeshScene* tmScene;
	Physics::MVPFluidSolver solver;
	Physics::MVPUpdater updator;
	CSGBoundaryView boundaryView;
	FloatView pressureCoeView;
	FloatView viscosityCoeView;
	FloatView timeStepView;
	FloatView radiusView;
	Button startButton;
	Button resetButton;
	int newId;

	Scene::World* world;
	Canvas* canvas;
};

	}
}