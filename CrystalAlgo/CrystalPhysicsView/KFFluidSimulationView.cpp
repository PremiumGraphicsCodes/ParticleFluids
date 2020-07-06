#include "KFFluidSimulationView.h"

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
	viscosityCoeView("ViscosityCoe", 100.0),
	timeStepView("TimeStep", 0.03)
{
	auto resetFunc = [=]() {
		reset();
	};
	resetButton.setFunction(resetFunc);
	add(&resetButton);

	boundaryView.setValue(Box3d(Vector3dd(-100, 0.0, -100.0), Vector3dd(100.0, 1000.0, 100.0)));
	add(&boundaryView);
	add(&pressureCoeView);
	add(&viscosityCoeView);
	add(&timeStepView);
}

void KFFluidSimulationView::onOk()
{
	auto world = getWorld();

	fluidScene = new KFFluidScene(getWorld()->getNextSceneId(), "KFFluid");
	getWorld()->getObjects()->addScene(fluidScene);

	this->reset();

	this->newId = fluidScene->getId();

	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	simulator.add(this->fluidScene);
	getWorld()->addAnimation(&simulator);
}

void KFFluidSimulationView::reset()
{
	this->fluidScene->clearParticles();

	this->fluidScene->setPressureCoe(pressureCoeView.getValue());
	this->fluidScene->setViscosityCoe(viscosityCoeView.getValue());

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 1; ++k) {
				auto mp = new MacroParticle(radius, Vector3dd(i * length, j * length, k * length));
				mp->distributePoints(5, 5, 5);
				fluidScene->addParticle(mp);
			}
		}
	}

	simulator.setBoundary(this->boundaryView.getValue());
	simulator.setTimeStep(timeStepView.getValue());
}
