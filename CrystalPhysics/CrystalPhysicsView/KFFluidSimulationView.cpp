#include "KFFluidSimulationView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../CrystalPhysics/KFFluidScene.h"
#include "../CrystalPhysics/KFFluidSolver.h"

#include "../../CrystalViewer/Command/Command.h"

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

namespace {
}


KFFluidSimulationView::KFFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("FluidSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary", model),
	pressureCoeView("PressureCoe", 100.0f),
	viscosityCoeView("ViscosityCoe", 10.0f),
	timeStepView("TimeStep", 0.025f),
	radiusView("SearchRadius", 1.0f)
{
	auto resetFunc = [=]() {
		reset();
	};
	resetButton.setFunction(resetFunc);
	add(&resetButton);

	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&timeStepView);
	add(&radiusView);
}

void KFFluidSimulationView::onOk()
{
	auto world = getWorld();

	fluidScene = new KFFluidScene(getWorld()->getNextSceneId(), "KFFluid");
	getWorld()->getScenes()->addScene(fluidScene);

	//boundaryScene = new KFFluidScene(getWorld()->getNextSceneId(), "KFBoundary");
	//getWorld()->getScenes()->addScene(boundaryScene);

	csgScene = new CSGBoundaryScene(getWorld()->getNextSceneId(), "CSG");
	csgScene->add(Box3d(Vector3dd(-100, 0, -100), Vector3dd(100, 100, 100)));

	this->reset();

	this->newId = fluidScene->getId();

	fluidScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	updator.add(fluidScene);

	//boundaryScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());

	getWorld()->addAnimation(&simulator);
	getWorld()->addAnimation(&updator);

	Command::Command command;
	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}

void KFFluidSimulationView::reset()
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
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, 1.0f);
				fluidScene->addParticle(mp);
			}
		}
	}

	/*
	const float weight = 5.0f;
	// bottom
	for (int i = 0; i < 20; ++i) {
		for (int j = -2; j < 0; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}
	boundaryScene->setBoundary(true);
	*/

	// bottom
	/*
	for (int i = -50; i < 0; ++i) {
		for (int j = -21; j < -20; ++j) {
			for (int k = -50; k < 50; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}
	*/


	// right
	/*
	for (int i = 20; i < 22; ++i) {
		for (int j = -2; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}

	// left
	for (int i = -1; i < 0; ++i) {
		for (int j = -1; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}

	// near
	for (int i = -1; i < 20; ++i) {
		for (int j = -1; j < 20; ++j) {
			for (int k = -1; k < 0; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}

	// far
	for (int i = -2; i < 20; ++i) {
		for (int j = -2; j < 20; ++j) {
			for (int k = 20; k < 22; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}
		*/

	simulator.clear();
	simulator.addFluidScene(fluidScene);
	simulator.addBoundary(csgScene);
	//simulator.addBoundaryScene(boundaryScene);
	//simulator.addBoundary(this->boundaryView.getBoundary());

	simulator.setMaxTimeStep(this->timeStepView.getValue());
	simulator.setupBoundaries();
}
