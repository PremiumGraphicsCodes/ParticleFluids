#include "FluidSimulationCommand.h"

#include "PublicLabels/FluidSimulationLabels.h"

#include "../CrystalPhysics/MVP/MVPFluidSolver.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

FluidSimulationCommand::Args::Args() :
	solverId(::SolverIdLabel, {})
{
	add(&solverId);
}

std::string FluidSimulationCommand::getName()
{
	return ::CommandNameLabel;
}

bool FluidSimulationCommand::execute(World* world)
{
	auto solver = world->findAnimatorById<MVPFluidSolver*>(args.solverId.getValue());
	solver->step();
	return true;
}
