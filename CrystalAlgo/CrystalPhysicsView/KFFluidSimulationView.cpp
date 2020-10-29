#include "KFFluidSimulationView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../CrystalPhysics/KFFluidScene.h"
#include "../CrystalPhysics/KFFluidSolver.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderSendLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

KFFluidSimulationView::KFFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("FluidSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	boundaryView("Boundary"),
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

	boundaryView.setValue(Box3d(Vector3dd(0,  -100.0, -50.0), Vector3dd(100.0, 1000.0, 100.0)));
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

	boundaryScene = new KFFluidScene(getWorld()->getNextSceneId(), "KFBoundary");
	getWorld()->getScenes()->addScene(boundaryScene);

	this->reset();

	this->newId = fluidScene->getId();

	fluidScene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());

	getWorld()->addAnimation(&simulator);

	Command::Command command;
	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}

void KFFluidSimulationView::reset()
{
	this->fluidScene->clearParticles();
	this->boundaryScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());

	const auto radius = 1.0;
	const auto length = radius * 2.0 * 1.25;
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
	for (int i = 0; i < 50; ++i) {
		for (int j = -1; j < 0; ++j) {
			for (int k = -50; k < 50; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}
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
	simulator.addBoundaryScene(boundaryScene);
	simulator.addSurface(this->boundaryView.getValue());

	simulator.setMaxTimeStep(this->timeStepView.getValue());

}
