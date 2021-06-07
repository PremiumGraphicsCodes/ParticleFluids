#include "SPHFlameSimulationView.h"

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
	SPHFlameConstant flameConstant;
}

SPHFlameSimulationView::SPHFlameSimulationView(World* model, Canvas* canvas) :
	IOkCancelView("SPHFlameSimulation", model, canvas),
	startButton("Start"),
	resetButton("Reset"),
	//	nextButton("Next"),
	timeStepView("TimeStep", 0.001f),
	pressureCoeView("PressureCoe", 1.0f),
	viscosityView("Viscosity", 1.0f),
	densityView("Density", 10.0f),
	boundaryView("Boundary")
{
	boundaryView.setValue(Box3d(Vector3dd(-100, 0, -100), Vector3dd(100, 1000, 100)));
	resetButton.setFunction([=]() { onReset(); });
	add(&resetButton);
	add(&timeStepView);
	add(&pressureCoeView);
	add(&viscosityView);
	add(&densityView);
	add(&boundaryView);
}

void SPHFlameSimulationView::onOk()
{
	auto world = getWorld();

	flame = new SPHFlameScene(getWorld()->getNextSceneId(), "Flame");
	getWorld()->getScenes()->addScene(flame);

	solver = new SPHFlameSolver();
	solver->add(flame);

	flame->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());

	this->onReset();

	Crystal::Command::Command command;
	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());

	getWorld()->addAnimation(solver);
}

void SPHFlameSimulationView::onReset()
{
	this->flame->clearParticles();

	const auto radius = 1.0;
	const auto length = radius * 2.0;
	::sphConstant.pressureCoe = pressureCoeView.getValue();
	::sphConstant.viscosityCoe = viscosityView.getValue();
	::sphConstant.effectLength = (length * 1.25);
	solver->setEffectLenth(::sphConstant.effectLength);
	::sphConstant.density = densityView.getValue();
	solver->setTimeStep(timeStepView.getValue());
	solver->setBoundary(boundaryView.getValue());
	solver->setExternalForce(Vector3df(0.0, -9.8, 0.0));

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 10; ++k) {
				auto mp = new SPHFlameParticle(Vector3dd(i * length, j * length, k * length), radius, &sphConstant, &flameConstant);
				flame->addParticle(mp);
			}
		}
	}
}
