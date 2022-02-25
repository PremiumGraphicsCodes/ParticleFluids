#include "MVPFluidSimulationView.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "../CrystalPhysics/MVP/MVPFluidSolver.h"
#include "../CrystalPhysics/MVP/MVPParticleBuilder.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Physics;

MVPFluidSimulationView::MVPFluidSimulationView(const std::string& name, World* model, Canvas* canvas) :
	IView(name),
	world(model),
	canvas(canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary", model),
	pressureCoeView("PressureCoe", 500.f),
	viscosityCoeView("ViscosityCoe", 50.0f),
	timeStepView("TimeStep", 0.01f),
	radiusView("SearchRadius", 2.00f)
{
	startButton.setFunction([=]() { onStart(); });
	add(&startButton);

	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);

	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&timeStepView);
	add(&radiusView);

	fluidScene = new MVPFluidScene(world->getNextSceneId(), "KFFluid");
	world->getScenes()->addScene(fluidScene);

	staticScene = new MVPFluidScene(world->getNextSceneId(), "Static");
	world->getScenes()->addScene(staticScene);

	emitterScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");
	world->getScenes()->addScene(emitterScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");


	world->addAnimation(&solver);
	world->addAnimation(&updator);

}

void MVPFluidSimulationView::onStart()
{
	onReset();

	fluidScene->getPresenter()->createView(world->getRenderer());
	emitterScene->getPresenter()->createView(world->getRenderer());
	staticScene->getPresenter()->createView(world->getRenderer());
	updator.add(fluidScene);
	updator.add(emitterScene);
	updator.add(staticScene);
}

void MVPFluidSimulationView::onReset()
{
	this->solver.clear();

	fluidScene->clearParticles();
	emitterScene->clearParticles();
	staticScene->clearParticles();

	//this->addFluid();
	this->addEmitter();

	csgScene->clearBoxes();
	csgScene->add(Box3d(Vector3dd(-100, 0, -100), Vector3dd(100, 100, 100)));

	//this->addEmitter();
}

void MVPFluidSimulationView::addFluid()
{
	this->fluidScene->clearParticles();
	//this->boundaryScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());
	
	this->staticScene->setPressureCoe(pressureCoeView.getValue());
	this->staticScene->setViscosityCoe(viscosityCoeView.getValue()*5.0);

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
					auto mp = builder.create(p, length, 3, 3, 3, 0.25f);
					//				mp->distributePoints(3, 3, 3, 1.00f);
					fluidScene->addParticle(mp);
				}
			}
		}
	}
	/*
	{
		MVPParticleBuilder builder;
		const auto radius = 0.10;
		const auto length = radius * 0.5;
		for (int i = 40; i < 60; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					const auto p = Vector3dd(i * length, j * length, k * length);
					auto mp = builder.create(p, length, 3, 3, 3, 0.25f);
					//				mp->distributePoints(3, 3, 3, 1.00f);
					staticScene->addParticle(mp);
				}
			}
		}

	}
	*/

	solver.clear();
	solver.addFluidScene(fluidScene);
	solver.addBoundaryScene(staticScene);
	solver.addBoundary(boundaryView.getBoundary());
	solver.setEffectLength(radiusView.getValue());

	solver.setMaxTimeStep(this->timeStepView.getValue());
	solver.setupBoundaries();
}

void MVPFluidSimulationView::addEmitter()
{
	this->emitterScene->clearParticles();
	//this->boundaryScene->clearParticles();

	this->emitterScene->setPressureCoe(pressureCoeView.getValue());
	this->emitterScene->setViscosityCoe(viscosityCoeView.getValue());


	emitterScene->addSource(Sphere3d(Vector3dd(0, 10, 0), 1.0));
	emitterScene->setStartEnd(0, 100);
	
	solver.clear();
	solver.addEmitterScene(emitterScene);

	solver.addBoundary(csgScene);

	solver.setMaxTimeStep(this->timeStepView.getValue());
	solver.setupBoundaries();
}