#include "FluidSimulationCommand.h"

#include "PublicLabels/FluidSimulationLabels.h"

#include "../CrystalPhysics/KFFluidSolver.h"

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
	auto solver = world->findAnimatorById<KFFluidSolver*>(args.solverId.getValue());
	solver->step();
	return true;
}
