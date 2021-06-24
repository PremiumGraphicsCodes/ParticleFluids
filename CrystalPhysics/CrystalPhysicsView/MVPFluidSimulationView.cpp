#include "MVPFluidSimulationView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "../CrystalPhysics/MVP/MVPFluidSolver.h"
#include "../CrystalPhysics/MVP/MVPParticleBuilder.h"

#include "../../CrystalViewer/Command/CameraFitCommand.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderSendLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

MVPFluidSimulationView::MVPFluidSimulationView(World* model, Canvas* canvas) :
	IView("MVPFluid"),
	world(model),
	canvas(canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary", model),
	pressureCoeView("PressureCoe", 0.25f),
	viscosityCoeView("ViscosityCoe", 10.0f),
	timeStepView("TimeStep", 0.03f),
	radiusView("SearchRadius", 2.25f)
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

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");

	world->addAnimation(&solver);
	world->addAnimation(&updator);

}

void MVPFluidSimulationView::onStart()
{
	onReset();

	fluidScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	updator.add(fluidScene);


	CameraFitCommand cameraCommand;
	cameraCommand.execute(world);
}

void MVPFluidSimulationView::onReset()
{
	fluidScene->clearParticles();
	this->addFluid();

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

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	MVPParticleBuilder builder;
	const auto radius = 2.00;
	const auto length = radius * 1.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
				const auto p = Vector3dd(i * length + 1, j * length + 1, k * length);
				auto mp = builder.create(p, length, 3, 3, 3, 1.0f);
//				mp->distributePoints(3, 3, 3, 1.00f);
				fluidScene->addParticle(mp);
			}
		}
	}

	solver.clear();
	solver.addFluidScene(fluidScene);
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