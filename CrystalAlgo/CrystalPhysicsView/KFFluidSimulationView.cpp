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
	pressureCoeView("PressureCoe", 1000),
	viscosityCoeView("ViscosityCoe", 25.0),
	timeStepView("TimeStep", 0.01),
	particleSystemSelectView("ParticleSystem", model, canvas),
	boundarySelectView("Boundary", model, canvas),
	radiusView("SearchRadius", 1.0)
{
	auto resetFunc = [=]() {
		reset();
	};
	resetButton.setFunction(resetFunc);
	add(&resetButton);

	boundaryView.setValue(Box3d(Vector3dd(-50, -100.0, -50.0), Vector3dd(50.0, 1000.0, 50.0)));
	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&timeStepView);
	add(&particleSystemSelectView);
	add(&boundarySelectView);
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

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	simulator.add(this->fluidScene);
	simulator.addBoundary(this->boundaryScene);
	getWorld()->addAnimation(&simulator);
}

void KFFluidSimulationView::reset()
{
	this->fluidScene->clearParticles();
	this->boundaryScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());

	const auto id = this->particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);

	/*
	const auto& ps = scene->getShape()->getParticles();
	for (auto p : ps) {
		auto pos = p->getPosition();
		auto mp = new KFMacroParticle(radiusView.getValue(), pos);
		mp->distributePoints(3, 3, 3);
		this->fluidScene->addParticle(mp);
		//writer.add(mp);
	}
	*/

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, 1.0f);
				fluidScene->addParticle(mp);
			}
		}
	}

	const float weight = 5.0f;
	// bottom
	for (int i = 0; i < 20; ++i) {
		for (int j = -1; j < 0; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new KFMacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(3, 3, 3, weight);
				boundaryScene->addParticle(mp);
			}
		}
	}

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
	*/

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



	simulator.setBoundary(this->boundaryView.getValue());
	simulator.setTimeStep(this->timeStepView.getValue());
}
