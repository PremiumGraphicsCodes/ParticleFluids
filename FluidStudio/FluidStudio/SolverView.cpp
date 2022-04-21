#include "SolverView.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPParticleBuilder.h"
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

SolverView::SolverView(const std::string& name, World* model, Canvas* canvas) :
	IView(name),
	world(model),
	canvas(canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	heatDiffuseCoeView("HeatDiffuseCoe", 100.0f),
	timeStepView("TimeStep", 0.01f),
	radiusView("SearchRadius", 2.00f),
	externalForceView("ExternalForce", Vector3dd(0.0, -9.8, 0.0)),
	buoyancyView("Buoyancy", Vector3df(0.0, 0.098, 0.0)),
	doExportView("Export", false),
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
	add(&timeStepView);
	add(&radiusView);
	add(&externalForceView);
	add(&buoyancyView);
	add(&doExportView);
	add(&exportDirecotryView);

	fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");
	world->getScenes()->addScene(fluidScene);

	staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");
	world->getScenes()->addScene(staticScene);

	emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	world->getScenes()->addScene(emitterScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");

	exporter = new SolverExporter(world);

	boundaryView.setValue(Box3dd(Vector3dd(0, 0, 0), Vector3dd(20, 20, 20)));

	world->addAnimation(&solver);
	world->addAnimation(&updator);
	world->addAnimation(exporter);
}

void SolverView::onStart()
{
	onReset();

	fluidScene->getPresenter()->createView(world->getRenderer());
	emitterScene->getPresenter()->createView(world->getRenderer());
	staticScene->getPresenter()->createView(world->getRenderer());
	updator.add(fluidScene);
	updator.add(emitterScene);
	updator.add(staticScene);
}

void SolverView::onReset()
{
	this->solver.clear();

	this->solver.setExternalForce(this->externalForceView.getValue());
	this->solver.setBuoyancy(this->buoyancyView.getValue());

	fluidScene->clearParticles();
	emitterScene->clearParticles();
	staticScene->clearParticles();

	this->addFluid();
	//this->addEmitter();

	csgScene->clearBoxes();
	csgScene->add(boundaryView.getValue());

	exporter->setSolver(&this->solver);
	exporter->setDirectory(this->exportDirecotryView.getPath());
	exporter->setActive(doExportView.getValue());
	//this->addEmitter();
}

void SolverView::addFluid()
{
	this->fluidScene->clearParticles();
	//this->boundaryScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());
	this->fluidScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

	this->staticScene->setPressureCoe(pressureCoeView.getValue());
	this->staticScene->setViscosityCoe(viscosityCoeView.getValue() * 5.0f);
	this->staticScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	{
		MVPParticleBuilder builder;
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = builder.create(p, length, 0.25f);
					//				mp->distributePoints(3, 3, 3, 1.00f);
					fluidScene->addParticle(mp);
				}
			}
		}
	}
	{
		MVPParticleBuilder builder;
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = 0; i < 20; ++i) {
			for (int j = -2; j < -1; ++j) {
				for (int k = 0; k < 20; ++k) {
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = builder.create(p, length, 0.25f);
					mp->setTemperature(1000.0f);
					mp->getMassParticles().front()->updateTemperature(1000.0f);
					staticScene->addParticle(mp);
					staticScene->setBoundary(true);
				}
			}
		}

	}

	solver.clear();
	solver.addFluidScene(fluidScene);
	solver.addBoundaryScene(staticScene);
	csgScene->add(boundaryView.getValue());
	solver.addBoundary(csgScene);
	solver.setEffectLength(radiusView.getValue());

	solver.setMaxTimeStep(this->timeStepView.getValue());
	solver.setupBoundaries();
}

void SolverView::addEmitter()
{
	this->emitterScene->clearParticles();
	this->emitterScene->clearSources();
	//this->boundaryScene->clearParticles();

	this->emitterScene->setPressureCoe(pressureCoeView.getValue());
	this->emitterScene->setViscosityCoe(viscosityCoeView.getValue());
	this->emitterScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

	for (int i = 0; i < 10; ++i) {
		emitterScene->addSource(Sphere3d(Vector3dd(0, i * 1.0, 0), 1.0));
	}
	emitterScene->setInitialVelocity(Vector3dd(10.0, 0.0, 0.0));
	emitterScene->setStartEnd(0, 100);


	solver.clear();
	solver.addEmitterScene(emitterScene);

	solver.addBoundary(csgScene);

	solver.setMaxTimeStep(this->timeStepView.getValue());
	solver.setupBoundaries();
}