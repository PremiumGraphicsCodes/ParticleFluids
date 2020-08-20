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

namespace {
	SPHConstant sphConstant(1.0f, 1000.0f, 100.0f, 0.0f, 2.25f);
	SPHKernel kernel;
	//sphConstant.
}

PBSPHFluidSimulationView::PBSPHFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("PBFluidSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.01),
	boundaryView("Boundary"),
	particleSystemSelectView("ParticleSystem", model, canvas, Scene::SceneType::ParticleSystemScene),
	outputDirectoryView("OutputDir")
{
	resetButton.setFunction([=]() { onReset(); });
	boundaryView.setValue(Box3d(Vector3dd(-50, 0.0, -50.0), Vector3dd(50.0, 1000.0, 50.0)));

	add(&particleSystemSelectView);
	add(&resetButton);
	add(&timeStepView);
	add(&boundaryView);
	add(&outputDirectoryView);
}

void PBSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	kernel = SPHKernel(2.25);
	this->fluidScene = new PBFluidScene(getWorld()->getNextSceneId(), "Fluid", kernel, sphConstant);
	this->simulator = new PBSPHSolver();

	
	onReset();
	getWorld()->getScenes()->addScene(this->fluidScene);
	auto newId = this->fluidScene->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());


	simulator->add(this->fluidScene);

	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	getWorld()->addAnimation(simulator);
	getWorld()->addAnimation(&writer);
}

void PBSPHFluidSimulationView::onReset()
{
	//this->simulator->clear();
	this->fluidScene->clearParticles();

	this->writer.reset();
	this->writer.setDirectryPath(outputDirectoryView.getPath());

	const auto id = this->particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);

	const auto& ps = scene->getShape()->getParticles();
	for (auto p : ps) {
		auto pos = p->getPosition();
		auto mp = new PBSPHParticle(pos, 1.0, this->fluidScene);
		this->fluidScene->addParticle(mp);
		writer.add(mp);
	}
	/*
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
	*/
	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());

}
