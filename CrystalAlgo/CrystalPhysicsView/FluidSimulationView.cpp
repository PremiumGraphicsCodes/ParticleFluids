#include "FluidSimulationView.h"

#include "../CrystalPhysics/FluidScene.h"
#include "../CrystalPhysics/FluidSimulator.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../CrystalViewer/Command/Command.h"

#include "../../CrystalViewer/Command/Public/ShaderBuildLabels.h"
#include "../../CrystalViewer/Command/Public/ShaderSendLabels.h"
#include "../../CrystalViewer/Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;
using namespace Crystal::Algo::Physics;

FluidSimulationView::FluidSimulationView(World* model, Canvas* canvas) :
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

	add(&resetButton);
}

void FluidSimulationView::onOk()
{
	auto world = getWorld();

//	mp1->setStatic(true);

	//auto mp2 = new MacroParticle(0.5, Vector3dd(0,1.0,0));
	//mp2->distributePoints(20, 20);

	FluidScene* fps = new FluidScene(getWorld()->getNextSceneId(), "Fluid");
	const auto radius = 0.1;
	const auto length = radius * 2.0;
	for (int i = -50; i < 50; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto mp = new MacroParticle(radius, Vector3dd(i * length, j + length, k));
				mp->distributePoints(10, 10, 10);
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

	//simulator.add(fps);

	auto simulator = new FluidSimulator();
	simulator->add(fps);
	getWorld()->addAnimation(simulator);
}