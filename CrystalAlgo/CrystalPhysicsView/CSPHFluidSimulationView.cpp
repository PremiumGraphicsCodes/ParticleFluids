#include "CSPHFluidSimulationView.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderSendLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"

#include "../CrystalPhysics/SPHConstant.h"

using namespace Crystal::Math;
//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Physics;

namespace {
	SPHConstant sphConstant;
}

CSPHFluidSimulationView::CSPHFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("CSPHFluidSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	nextButton("Next"),
	timeStepView("TimeStep", 0.001),
	pressureCoeView("PressureCoe", 1.0),
	viscosityView("Viscosity", 1.0),
	densityView("Density", 10.0),
	newId(-1)
{
	auto func = [=]() {
		simulator.simulate(0.01);
		Command::Command command;
		command.create(ShaderSendLabels::CommandNameLabel);
		command.setArg(ShaderSendLabels::IdLabel, newId);
		command.execute(getWorld());
	};
	nextButton.setFunction(func);
	add(&nextButton);

	auto resetFunc = [=]() {
		reset();
	};
	resetButton.setFunction(resetFunc);
	add(&resetButton);
	add(&timeStepView);
	add(&pressureCoeView);
	add(&viscosityView);
	add(&densityView);
}

void CSPHFluidSimulationView::onOk()
{
	auto world = getWorld();

	fluidScene = new CSPHFluidScene(getWorld()->getNextSceneId(), "Fluid");
	getWorld()->getScenes()->addScene(fluidScene);

	this->reset();

	this->newId = fluidScene->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	auto simulator = new CSPHSolver();
	simulator->add(fluidScene);
	simulator->setExternalForce(Vector3df(0.0, -9.8, 0.0));
	getWorld()->addAnimation(simulator);
}

void CSPHFluidSimulationView::reset()
{
	this->fluidScene->clearParticles();

	const auto radius = 0.1;
	const auto length = radius * 2.0;
	::sphConstant.pressureCoe = pressureCoeView.getValue();
	::sphConstant.viscosityCoe = viscosityView.getValue();
	::sphConstant.effectLength = (length * 1.25);
	::sphConstant.density = densityView.getValue();
	simulator.setTimeStep(timeStepView.getValue());

	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 1; ++k) {
				auto mp = new CSPHParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant);
				fluidScene->addParticle(mp);
			}
		}
	}
}
