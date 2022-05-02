#include "FluidView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

FluidView::FluidView(const std::string& name, World* model, Canvas* canvas) :
	IView(name),
	boundaryView("Boundary"),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	heatDiffuseCoeView("HeatDiffuseCoe", 100.0f),
	dragHeatCoeView("DragHeatCoe", 0.0),
	dragForceCoeView("DragForceCoe", 0.0)
{
	/*
	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&heatDiffuseCoeView);
	add(&dragHeatCoeView);
	add(&dragForceCoeView);

	fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");
	world->getScenes()->addScene(fluidScene);

	staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");
	world->getScenes()->addScene(staticScene);

	emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	world->getScenes()->addScene(emitterScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");

	exporter = new SolverExporter(world);

	boundaryView.setValue(Box3dd(Vector3dd(-20, 0, -20), Vector3dd(20, 20, 20)));

	world->addAnimation(&solver);
	world->addAnimation(&updator);
	world->addAnimation(exporter);
	*/
}

void FluidView::addFluid()
{
	/*
	this->fluidScene->clearParticles();
	//this->boundaryScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());
	this->fluidScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	this->fluidScene->setDragForceCoe(dragForceCoeView.getValue());
	this->fluidScene->setDragHeatCoe(dragHeatCoeView.getValue());

	this->staticScene->setPressureCoe(pressureCoeView.getValue());
	this->staticScene->setViscosityCoe(viscosityCoeView.getValue() * 5.0f);
	this->staticScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = -20; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = -20; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = fluidScene->create(p, length, 0.25f, 300.0f);
					//				mp->distributePoints(3, 3, 3, 1.00f);
					fluidScene->addParticle(mp);
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
					auto mp = staticScene->create(p, length, 0.25f, 2000.0f);
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
	*/
}

void FluidView::addEmitter()
{
	/*
	this->emitterScene->clearParticles();
	this->emitterScene->clearSources();
	//this->boundaryScene->clearParticles();

	this->emitterScene->setPressureCoe(pressureCoeView.getValue());
	this->emitterScene->setViscosityCoe(viscosityCoeView.getValue());
	this->emitterScene->setHeatDiffuseCoe(heatDiffuseCoeView.getValue());
	this->emitterScene->setDragForceCoe(dragForceCoeView.getValue());
	this->emitterScene->setDragHeatCoe(dragHeatCoeView.getValue());

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


	solver.clear();
	solver.addEmitterScene(emitterScene);

	solver.addBoundary(csgScene);

	solver.setMaxTimeStep(this->timeStepView.getValue());
	solver.setupBoundaries();
	*/
}