#include "PBSPHFluidSimulationView.h"

#include "../CrystalPhysics/PBFluidScene.h"
#include "../CrystalPhysics/PBSPHSolver.h"
#include "../CrystalPhysics/PBSPHParticle.h"

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
	SPHKernel kernel;
	//sphConstant.
}

PBSPHFluidSimulationView::PBSPHFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("PBFluidSimulation", model, canvas),
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

void PBSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	kernel.setEffectLength(2.25);
	this->fluidScene = new PBFluidScene(getWorld()->getNextSceneId(), "Fluid", kernel, sphConstant);
	this->simulator = new PBSPHSolver();

	
	reset();
	getWorld()->getScenes()->addScene(this->fluidScene);
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

void PBSPHFluidSimulationView::reset()
{
	//this->simulator->clear();
	this->fluidScene->clearParticles();

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
	simulator->setBoundary(boundaryView.getValue());
	simulator->setTimeStep(timeStepView.getValue());
}
