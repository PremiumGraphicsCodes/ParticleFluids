#include "PhysicsSolverCreateCommand.h"

#include "PublicLabels/PhysicsSolverCreateLabels.h"

#include "../CrystalPhysics/KFFluidSolver.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverCreateCommand::getName()
{
	return ::CommandNameLabel;
}

PhysicsSolverCreateCommand::Args::Args()
{
}

PhysicsSolverCreateCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

PhysicsSolverCreateCommand::PhysicsSolverCreateCommand() :
	ICommand(&args, &results)
{}

bool PhysicsSolverCreateCommand::execute(World* world)
{
	auto solver = new KFFluidSolver(world->getNextSceneId());
	world->addAnimation(solver);

	results.newId.setValue(solver->getId());

	return true;
}
