#include "PBSPHFluidSimulationView.h"

#include "../CrystalPhysics/PBFluidScene.h"
#include "../CrystalPhysics/PBSPHSolver.h"
#include "../CrystalPhysics/PBSPHParticle.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderSendLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

PBSPHFluidSimulationView::PBSPHFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("PBFluidSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.01),
	radiusView("Radius", 1.0),
	effectLengthView("EffectLength", 2.25),
	densityView("Density", 1.0),
	boundaryView("Boundary"),
	particleSystemSelectView("ParticleSystem", model, canvas, Scene::SceneType::ParticleSystemScene),
	boundarySelectView("Boundary", model, canvas, Scene::SceneType::ParticleSystemScene),
	stiffnessView("Stiffness", 0.05),
	vicsocityView("Viscosity", 0.1)
{
	resetButton.setFunction([=]() { onReset(); });
	boundaryView.setValue(Box3d(Vector3dd(-50, 0.0, -50.0), Vector3dd(50.0, 1000.0, 50.0)));

	add(&particleSystemSelectView);
	add(&boundarySelectView);
	add(&resetButton);
	add(&timeStepView);
	add(&radiusView);
	add(&densityView);
	add(&effectLengthView);
	add(&boundaryView);
	add(&stiffnessView);
	add(&vicsocityView);
}

void PBSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	this->fluidScene = new PBFluidScene(getWorld()->getNextSceneId(), "Fluid");
	this->boundaryScene = new PBFluidScene(getWorld()->getNextSceneId(), "Boundary");
	this->simulator = new PBSPHSolver();

	/*
	const auto id = this->particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}
	*/
	
	onReset();

	getWorld()->getScenes()->addScene(this->fluidScene);
	auto newId = this->fluidScene->getId();

	getWorld()->getScenes()->addScene(this->boundaryScene);
	auto boundaryId = this->boundaryScene->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, boundaryId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	simulator->add(this->fluidScene);
	simulator->add(this->boundaryScene);

	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	getWorld()->addAnimation(simulator);
	//getWorld()->addAnimation(&writer);
}

void PBSPHFluidSimulationView::onReset()
{
	//this->simulator->clear();
	this->fluidScene->clearParticles();
	this->fluidScene->setEffectLength(this->effectLengthView.getValue());
	this->fluidScene->setRestDensity(this->densityView.getValue());
	this->fluidScene->setStiffness(this->stiffnessView.getValue());
	this->fluidScene->setVicsosity(this->vicsocityView.getValue());

	this->boundaryScene->clearParticles();
	this->boundaryScene->setEffectLength(this->effectLengthView.getValue());
	this->boundaryScene->setRestDensity(this->densityView.getValue());
	this->boundaryScene->setStiffness(this->stiffnessView.getValue() * 10.0f);
	this->boundaryScene->setVicsosity(this->vicsocityView.getValue());
	this->boundaryScene->setIsBoundary(true);

	//this->writer.reset();
//	this->writer.setDirectryPath(outputDirectoryView.getPath());

	const auto id = this->particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);

	/*
	const auto& ps = scene->getShape()->getParticles();
	for (auto p : ps) {
		auto pos = p->getPosition();
		auto mp = new PBSPHParticle(pos, radiusView.getValue(), this->fluidScene);
		this->fluidScene->addParticle(mp);
		writer.add(mp);
	}
	*/

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->fluidScene);
				this->fluidScene->addParticle(mp);
			}
		}
	}

	for (int i = 0; i < 20; ++i) {
		for (int j = -2; j < 0; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->boundaryScene);
				this->boundaryScene->addParticle(mp);
			}
		}
	}

	/*
	for (int i = 20; i < 22; ++i) {
		for (int j = -2; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->boundaryScene);
				this->boundaryScene->addParticle(mp);
			}
		}
	}

	for (int i = -2; i < 0; ++i) {
		for (int j = -2; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->boundaryScene);
				this->boundaryScene->addParticle(mp);
			}
		}
	}

	for (int i = -2; i < 20; ++i) {
		for (int j = -2; j < 20; ++j) {
			for (int k = -2; k < 0; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->boundaryScene);
				this->boundaryScene->addParticle(mp);
			}
		}
	}

	for (int i = -2; i < 20; ++i) {
		for (int j = -2; j < 20; ++j) {
			for (int k = 20; k < 22; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, this->boundaryScene);
				this->boundaryScene->addParticle(mp);
			}
		}
	}
	*/


	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());
}
