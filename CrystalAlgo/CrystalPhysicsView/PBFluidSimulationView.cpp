#include "PBFluidSimulationView.h"

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
	SPHConstant sphConstant;
}

PBFluidSimulationView::PBFluidSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("PBFluidSimulation", model, canvas),
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

	add(&resetButton);
}

void PBFluidSimulationView::onOk()
{
	auto world = getWorld();

	auto fps = new PBFluidScene(getWorld()->getNextSceneId(), "Fluid");
	const auto radius = 0.1;
	const auto length = radius * 2.0;
	for (int i = -50; i < 50; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto mp = new PBSPHParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant);
				fps->addParticle(mp);
			}
		}
	}
	getWorld()->getObjects()->addScene(fps);
	this->newId = fps->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	//auto simulator = new PBSPHSolver();
	//simulator->add(fps);
	//getWorld()->addAnimation(simulator);
}