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

	mainModel->fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");
	world->getScenes()->addScene(mainModel->fluidScene);

	mainModel->staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");
	world->getScenes()->addScene(mainModel->staticScene);

	mainModel->emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	world->getScenes()->addScene(mainModel->emitterScene);

	mainModel->csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");

	exporter = new SolverExporter(world);

	boundaryView.setValue(Box3dd(Vector3dd(-20, 0, -20), Vector3dd(20, 20, 20)));

	world->addAnimation(&mainModel->solver);
	world->addAnimation(&mainModel->updator);
	world->addAnimation(exporter);
}

void SolverView::onStart()
{
	onReset();

	model->fluidScene->getPresenter()->createView(world->getRenderer());
	model->emitterScene->getPresenter()->createView(world->getRenderer());
	model->staticScene->getPresenter()->createView(world->getRenderer());
	model->updator.add(model->fluidScene);
	model->updator.add(model->emitterScene);
	model->updator.add(model->staticScene);
}

void SolverView::onReset()
{
	model->solver.clear();

	model->solver.setExternalForce(this->externalForceView.getValue());
	model->solver.setBuoyancy(this->buoyancyView.getValue());

	model->fluidScene->clearParticles();
	model->emitterScene->clearParticles();
	model->staticScene->clearParticles();


	//this->addFluid();
	this->addEmitter();

	model->csgScene->clearBoxes();
	model->csgScene->add(boundaryView.getValue());

	exporter->reset();
	exporter->setSolver(&model->solver);
	exporter->setDirectory(this->exportDirecotryView.getPath());
	exporter->setActive(doExportView.getValue());
	exporter->setExportInterval(this->exportIntervalView.getValue());
	//this->addEmitter();
}

void SolverView::addFluid()
{
	model->fluidScene->clearParticles();
	//this->boundaryScene->clearParticles();

	model->fluidScene->setPressureCoe(pressureCoeView.getValue());
	model->fluidScene->setViscosityCoe(viscosityCoeView.getValue());
	model->fluidScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	model->fluidScene->setDragForceCoe(dragForceCoeView.getValue());
	model->fluidScene->setDragHeatCoe(dragHeatCoeView.getValue());

	model->staticScene->setPressureCoe(pressureCoeView.getValue());
	model->staticScene->setViscosityCoe(viscosityCoeView.getValue() * 5.0f);
	model->staticScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i =-20; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = -20; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = model->fluidScene->create(p, length, 0.25f, 300.0f);
					//				mp->distributePoints(3, 3, 3, 1.00f);
					model->fluidScene->addParticle(mp);
				}
			}
		}
	}
	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = -10; i < 10; ++i) {
			for (int j = -1; j < 0; ++j) {
				for (int k = -10; k < 10; ++k) {
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = model->staticScene->create(p, length, 0.25f, 2000.0f);
					model->staticScene->addParticle(mp);
					model->staticScene->setBoundary(true);
				}
			}
		}

	}

	model->solver.clear();
	model->solver.addFluidScene(model->fluidScene);
	model->solver.addBoundaryScene(model->staticScene);
	model->csgScene->add(boundaryView.getValue());
	model->solver.addBoundary(model->csgScene);
	model->solver.setEffectLength(radiusView.getValue());

	model->solver.setMaxTimeStep(this->timeStepView.getValue());
	model->solver.setupBoundaries();
}

void SolverView::addEmitter()
{
	model->emitterScene->clearParticles();
	model->emitterScene->clearSources();
	//this->boundaryScene->clearParticles();

	model->emitterScene->setPressureCoe(pressureCoeView.getValue());
	model->emitterScene->setViscosityCoe(viscosityCoeView.getValue());
	model->emitterScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	model->emitterScene->setDragForceCoe(dragForceCoeView.getValue());
	model->emitterScene->setDragHeatCoe(dragHeatCoeView.getValue());

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 1; ++j) {
			for (int k = 0; k < 10; ++k) {
				model->emitterScene->addSource(Sphere3d(Vector3dd(i * 0.5, j * 0.5, k * 0.5), 0.5));
			}
		}
	}
	model->emitterScene->setInitialTemperature(1000.0f);
	model->emitterScene->setLifeLimit(100);
	model->emitterScene->setInterval(2);
	model->emitterScene->setInitialVelocity(Vector3dd(0.0, 0.0, 0.0));
	model->emitterScene->setStartEnd(0, 10000);


	model->solver.clear();
	model->solver.addEmitterScene(model->emitterScene);

	model->solver.addBoundary(model->csgScene);

	model->solver.setMaxTimeStep(this->timeStepView.getValue());
	model->solver.setupBoundaries();
}