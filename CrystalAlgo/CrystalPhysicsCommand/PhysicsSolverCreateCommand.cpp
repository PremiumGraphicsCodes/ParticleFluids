#include "PhysicsSolverCreateCommand.h"

//#include "PublicLabels/FluidSceneCreateLabels.h"

#include "../CrystalPhysics/KFFluidSolver.h"
#include "../CrystalPhysics/KFFluidScene.h"
#include "../CrystalPhysics/CSGBoundaryScene.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverCreateCommand::getName()
{
	return "PhysicsSolverCreate";
}

PhysicsSolverCreateCommand::Args::Args() :
	fluidSceneIds("FluidSceneIds", {}),
	csgBoundarySceneIds("CSGBoundarySceneIds", {}),
	timeStep("TimeStep", 0.03f),
	name("Name", std::string("FluidScene"))
{
	add(&fluidSceneIds);
	add(&csgBoundarySceneIds);
	add(&timeStep);
	add(&name);
}

PhysicsSolverCreateCommand::Results::Results() :
	newId("NewId", -1)
{
	add(&newId);
}

PhysicsSolverCreateCommand::PhysicsSolverCreateCommand() :
	ICommand(&args, &results)
{}

bool PhysicsSolverCreateCommand::execute(World* world)
{
	const auto ids = args.fluidSceneIds.getValue();
	auto solver = new KFFluidSolver();
	for (const auto id : ids) {
		auto scene = world->getScenes()->findSceneById<KFFluidScene*>(id);
		if (scene->isBoundary()) {
			solver->addBoundaryScene(scene);
		}
		else {
			solver->addFluidScene(scene);
		}
	}

	const auto boundaryIds = args.csgBoundarySceneIds.getValue();
	for (const auto id : boundaryIds) {
		auto scene = world->getScenes()->findSceneById<CSGBoundaryScene*>(id);
		solver->addBoundary(scene);
	}
	world->addAnimation(solver);

	return true;
}
