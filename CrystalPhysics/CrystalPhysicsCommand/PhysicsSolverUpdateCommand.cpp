#include "PhysicsSolverUpdateCommand.h"

#include "PublicLabels/PhysicsSolverUpdateLabels.h"

#include "../CrystalPhysics/KFFluidSolver.h"
#include "../CrystalPhysics/KFFluidScene.h"
#include "../CrystalPhysics/CSGBoundaryScene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

PhysicsSolverUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	fluidSceneIds(::FluidSceneIdsLabel, {}),
	csgBoundarySceneIds(::CSGBoundarySceneIdsLabel, {}),
	timeStep(::TimeStepLabel, 0.03f),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&fluidSceneIds);
	add(&csgBoundarySceneIds);
	add(&timeStep);
	add(&name);
}

PhysicsSolverUpdateCommand::Results::Results()
{
}

PhysicsSolverUpdateCommand::PhysicsSolverUpdateCommand() :
	ICommand(&args, &results)
{}

bool PhysicsSolverUpdateCommand::execute(World* world)
{
	auto solver = world->findAnimatorById<KFFluidSolver*>(args.id.getValue());
	if (solver == nullptr) {
		return false;
	}

	solver->clear();

	solver->setMaxTimeStep(args.timeStep.getValue());

	const auto ids = args.fluidSceneIds.getValue();

	for (const auto id : ids) {
		auto scene = world->getScenes()->findSceneById<KFFluidScene*>(id);
		if (scene->isBoundary()) {
			solver->addBoundaryScene(scene);
		}
		else {
			solver->addFluidScene(scene);
		}
	}
	solver->setupBoundaries();

	const auto boundaryIds = args.csgBoundarySceneIds.getValue();
	for (const auto id : boundaryIds) {
		auto scene = world->getScenes()->findSceneById<CSGBoundaryScene*>(id);
		solver->addBoundary(scene);
	}

	return true;
}
