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
}

void FluidSimulationView::onOk()
{
	auto world = getWorld();

	auto mp1 = new MacroParticle(0.5, Vector3dd(0,0,0));
	mp1->distributePoints(10, 10);
	mp1->setStatic(true);

	auto mp2 = new MacroParticle(0.5, Vector3dd(0,1.0,0));
	mp2->distributePoints(10, 10);

	FluidScene* fps = new FluidScene(getWorld()->getNextSceneId(), "Fluid");
	fps->addParticle(mp1);
	fps->addParticle(mp2);
	getWorld()->getObjects()->addScene(fps);
	this->newId = fps->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	simulator.add(fps);

	/*
	for (int i = 0; i < 1; ++i) {
		simulator.simulate(0.01);
		command.create(ShaderSendLabels::CommandNameLabel);
		command.setArg(ShaderSendLabels::IdLabel, newId);
		command.execute(getWorld());
	}
	*/
}