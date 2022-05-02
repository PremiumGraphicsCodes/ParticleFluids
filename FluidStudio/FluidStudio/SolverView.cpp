#include "SolverView.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "CrystalPhysics/CrystalPhysics/Boundary/CSGBoundaryScene.h"
#include "SolverExporter.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalScene/Scene/IAnimator.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsSolverExportCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

SolverView::SolverView(const std::string& name, World* world, Canvas* canvas, MainModel* mainModel) :
	IView(name),
	model(mainModel),
	world(world),
	canvas(canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	heatDiffuseCoeView("HeatDiffuseCoe", 100.0f),
	dragHeatCoeView("DragHeatCoe", 0.0),
	dragForceCoeView("DragForceCoe", 0.0),
	timeStepView("TimeStep", 0.01f),
	radiusView("SearchRadius", 2.00f),
	externalForceView("ExternalForce", Vector3dd(0.0, -9.8, 0.0)),
	buoyancyView("Buoyancy", Vector3df(0.0, 0.098, 0.0)),
	doExportView("Export", false),
	exportIntervalView("Interval", 5),
	exportDirecotryView("ExportDir", "./")
{
	startButton.setFunction([=]() { onStart(); });
	add(&startButton);

	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);

	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&heatDiffuseCoeView);
	add(&dragHeatCoeView);
	add(&dragForceCoeView);
	add(&timeStepView);
	add(&radiusView);
	add(&externalForceView);
	add(&buoyancyView);
	add(&doExportView);
	add(&exportIntervalView);
	add(&exportDirecotryView);

	mainModel->csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");

	model->exporter = new SolverExporter(world);

	boundaryView.setValue(Box3dd(Vector3dd(-20, 0, -20), Vector3dd(20, 20, 20)));

	world->addAnimation(&model->solver);
	world->addAnimation(&model->updator);
	world->addAnimation(model->exporter);
}

void SolverView::onStart()
{
	onReset();
}

void SolverView::onReset()
{
	model->resetSolver();
	//model->solver.clear();

	model->solver.setExternalForce(this->externalForceView.getValue());
	model->solver.setBuoyancy(this->buoyancyView.getValue());


	//this->addEmitter();

	//model->solver.clear();
	model->csgScene->add(boundaryView.getValue());
	model->solver.addBoundary(model->csgScene);
	model->solver.setEffectLength(radiusView.getValue());

	model->solver.setMaxTimeStep(this->timeStepView.getValue());
	model->solver.setupBoundaries();


	model->csgScene->clearBoxes();
	model->csgScene->add(boundaryView.getValue());

	model->exporter->reset();
	model->exporter->setSolver(&model->solver);
	model->exporter->setDirectory(this->exportDirecotryView.getPath());
	model->exporter->setActive(doExportView.getValue());
	model->exporter->setExportInterval(this->exportIntervalView.getValue());
	//this->addEmitter();
}

void SolverView::addEmitter()
{
	auto emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");

	emitterScene->setPressureCoe(pressureCoeView.getValue());
	emitterScene->setViscosityCoe(viscosityCoeView.getValue());
	emitterScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	emitterScene->setDragForceCoe(dragForceCoeView.getValue());
	emitterScene->setDragHeatCoe(dragHeatCoeView.getValue());

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 1; ++j) {
			for (int k = 0; k < 10; ++k) {
				emitterScene->addSource(Sphere3d(Vector3dd(i * 0.5, j * 0.5, k * 0.5), 0.5));
			}
		}
	}
	emitterScene->setInitialTemperature(1000.0f);
	emitterScene->setLifeLimit(100);
	emitterScene->setInterval(2);
	emitterScene->setInitialVelocity(Vector3dd(0.0, 0.0, 0.0));
	emitterScene->setStartEnd(0, 10000);

	emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	emitterScene->getPresenter()->createView(world->getRenderer());

	world->getScenes()->addScene(emitterScene);


	model->solver.clear();
	model->solver.addEmitterScene(emitterScene);

	model->solver.addBoundary(model->csgScene);

	model->solver.setMaxTimeStep(this->timeStepView.getValue());
	model->solver.setupBoundaries();
}