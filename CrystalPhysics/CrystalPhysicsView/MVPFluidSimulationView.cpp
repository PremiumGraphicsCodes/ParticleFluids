#include "MVPFluidSimulationView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../CrystalPhysics/MVP/KFFluidScene.h"
#include "../CrystalPhysics/MVP/KFFluidEmitterScene.h"
#include "../CrystalPhysics/MVP/KFFluidSolver.h"

#include "../../CrystalViewer/Command/CameraFitCommand.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderSendLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/Math/Quad3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

MVPFluidSimulationView::MVPFluidSimulationView(World* model, Canvas* canvas) :
	IView("FluidSimulation"),
	world(model),
	canvas(canvas),
	addFluidButton("AddFluid"),
	addEmitterButton("AddEmitter"),
	startButton("Start"),
//	resetButton("Reset"),
	boundaryView("Boundary", model),
	pressureCoeView("PressureCoe", 100.0f),
	viscosityCoeView("ViscosityCoe", 10.0f),
	timeStepView("TimeStep", 0.025f),
	radiusView("SearchRadius", 1.0f)
{
	addFluidButton.setFunction([=]() { onAddFluid(); });
	add(&addFluidButton);

	addEmitterButton.setFunction([=]() {onAddEmitter(); });
	add(&addEmitterButton);

	startButton.setFunction([=]() { onStart(); });
	add(&startButton);

	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&timeStepView);
	add(&radiusView);
}

void MVPFluidSimulationView::onStart()
{
	fluidScene = new KFFluidScene(world->getNextSceneId(), "KFFluid");
	world->getScenes()->addScene(fluidScene);

	emitterScene = new KFFluidEmitterScene(world->getNextSceneId(), "KFEmitter");
	world->getScenes()->addScene(emitterScene);

	//boundaryScene = new KFFluidScene(getWorld()->getNextSceneId(), "KFBoundary");
	//getWorld()->getScenes()->addScene(boundaryScene);

	csgScene = new CSGBoundaryScene(world->getNextSceneId(), "CSG");
	csgScene->add(Box3d(Vector3dd(-100, 0, -100), Vector3dd(100, 100, 100)));

	//this->onAddFluid();
	this->onAddEmitter();


	//fluidScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	//updator.add(fluidScene);

	emitterScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	updator.add(emitterScene);

	//boundaryScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());

	world->addAnimation(&solver);
	world->addAnimation(&updator);

	CameraFitCommand cameraCommand;
	cameraCommand.execute(world);
}

void MVPFluidSimulationView::onAddFluid()
{
	this->fluidScene->clearParticles();
	//this->boundaryScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());

	//this->boundaryScene->setPressureCoe(pressureCoeView.getValue());
	//this->boundaryScene->setViscosityCoe(viscosityCoeView.getValue());

	const auto radius = 1.0;
	const auto length = radius * 2.25;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new MVPVolumeParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, 1.0f);
				fluidScene->addParticle(mp);
			}
		}
	}

	solver.clear();
	solver.addFluidScene(fluidScene);
	solver.addBoundary(csgScene);

	solver.setMaxTimeStep(this->timeStepView.getValue());
	solver.setupBoundaries();
}

void MVPFluidSimulationView::onAddEmitter()
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