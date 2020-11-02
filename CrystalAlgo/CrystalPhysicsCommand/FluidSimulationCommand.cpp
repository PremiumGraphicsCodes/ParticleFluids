#include "FluidSimulationCommand.h"

#include "PublicLabels/FluidSimulationLabels.h"

#include "../CrystalPhysics/KFFluidScene.h"
#include "../CrystalPhysics/KFFluidSolver.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;

FluidSimulationCommand::Args::Args() :
	fluidSceneIds(::FluidSceneIdsLabel, {}),
	timeStep(::TimeStepLabel, 0.03f)
{
	add(&fluidSceneIds);
	add(&timeStep);
}

std::string FluidSimulationCommand::getName()
{
	return ::CommandNameLabel;
}

bool FluidSimulationCommand::execute(World* world)
{
	const auto ids = args.fluidSceneIds.getValue();
	KFFluidSolver solver;
	for (const auto id : ids) {
		auto scene = world->getScenes()->findSceneById<KFFluidScene*>(id);
		solver.addFluidScene(scene);
	}
	solver.step();
	return true;
}
