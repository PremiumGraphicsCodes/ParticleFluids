#include "DFSPHFluidSimulationView.h"

#include "../CrystalPhysics/DFFluidScene.h"
#include "../CrystalPhysics/DFFluidSolver.h"
#include "../CrystalPhysics/DFSPHParticle.h"
#include "../CrystalPhysics/SPHConstant.h"

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

namespace {
	SPHConstant sphConstant(1.0f, 1000.0f, 100.0f, 0.0f, 2.25f);
	SPHKernel sphKernel;
	//sphConstant.
}

DFSPHFluidSimulationView::DFSPHFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("DFSPHFluidSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	timeStepView("TimeStep", 0.01),
	boundaryView("Boundary")
{

	auto resetFunc = [=]() {
		reset();
	};
	resetButton.setFunction(resetFunc);
	add(&resetButton);

	boundaryView.setValue(Box3d(Vector3dd(-50, 0.0, -50.0), Vector3dd(50.0, 1000.0, 50.0)));


	add(&timeStepView);
	add(&boundaryView);
}

void DFSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	this->fluidScene = new DFFluidScene(getWorld()->getNextSceneId(), "DFFluid");
	this->simulator = new DFFluidSolver();


	reset();
	getWorld()->getObjects()->addScene(this->fluidScene);
	this->newId = this->fluidScene->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());


	simulator->add(this->fluidScene);

	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	getWorld()->addAnimation(simulator);
}

void DFSPHFluidSimulationView::reset()
{
	//this->simulator->clear();
	this->fluidScene->clearParticles();

	auto mp = new DFSPHParticle(Vector3dd(0,0,0), 1.0, &sphConstant, &sphKernel);
	this->fluidScene->addParticle(mp);

	/*
	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			for (int k = 0; k < 20; ++k) {
				auto mp = new DFSPHParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant);
				this->fluidScene->addParticle(mp);
			}
		}
	}
	*/
	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());
}
