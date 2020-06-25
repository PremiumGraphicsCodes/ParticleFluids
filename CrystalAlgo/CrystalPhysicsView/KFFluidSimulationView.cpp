#include "KFFluidSimulationView.h"

#include "../CrystalPhysics/FluidScene.h"
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
	nextButton("Next")
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
}

void KFFluidSimulationView::onOk()
{
	auto world = getWorld();

	fluidScene = new FluidScene(getWorld()->getNextSceneId(), "Fluid");
	getWorld()->getObjects()->addScene(fluidScene);

	this->reset();

	this->newId = fluidScene->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	auto simulator = new KFFluidSolver();
	simulator->setBoundary(Box3d(Vector3dd(-20.0, 0.0, -20.0), Vector3dd(20.0, 1000.0, 20.0)));
	simulator->add(this->fluidScene);
	getWorld()->addAnimation(simulator);
}

void KFFluidSimulationView::reset()
{
	this->fluidScene->clearParticles();

	const auto radius = 0.1;
	const auto length = radius * 2.0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 1; ++k) {
				auto mp = new MacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(5, 5);
				fluidScene->addParticle(mp);
			}
		}
	}
}
