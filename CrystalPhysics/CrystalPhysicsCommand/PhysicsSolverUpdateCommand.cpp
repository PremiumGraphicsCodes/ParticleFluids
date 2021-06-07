#include "PhysicsSolverUpdateCommand.h"

#include "PublicLabels/PhysicsSolverUpdateLabels.h"

#include "../CrystalPhysics/MVP/MVPFluidSolver.h"
#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../CrystalPhysics/MVP/KFFluidEmitterScene.h"
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
	emitterSceneIds(::EmitterSceneIdsLabel, {}),
	csgBoundarySceneIds(::CSGBoundarySceneIdsLabel, {}),
	meshBoundarySceneIds(::MeshBoundarySceneIdsLabel, {}),
	effectLength(::EffectLengthLabel, 2.0f),
	timeStep(::TimeStepLabel, 0.03f),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&fluidSceneIds);
	add(&emitterSceneIds);
	add(&csgBoundarySceneIds);
	add(&meshBoundarySceneIds);
	add(&effectLength);
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
	auto solver = world->findAnimatorById<MVPFluidSolver*>(args.id.getValue());
	if (solver == nullptr) {
		return false;
	}

	solver->setEffectLength(args.effectLength.getValue());

	solver->clear();

	solver->setMaxTimeStep(args.timeStep.getValue());

	const auto ids = args.fluidSceneIds.getValue();

	for (const auto id : ids) {
		auto scene = world->getScenes()->findSceneById<MVPFluidScene*>(id);
		if (scene->isBoundary()) {
			solver->addBoundaryScene(scene);
		}
		else {
			solver->addFluidScene(scene);
		}
	}

	const auto emitterIds = args.emitterSceneIds.getValue();

	for (const auto id : emitterIds) {
		auto scene = world->getScenes()->findSceneById<KFFluidEmitterScene*>(id);
		solver->addEmitterScene(scene);
	}

	const auto boundaryIds = args.csgBoundarySceneIds.getValue();
	for (const auto id : boundaryIds) {
		auto scene = world->getScenes()->findSceneById<CSGBoundaryScene*>(id);
		solver->addBoundary(scene);
	}

	solver->setupBoundaries();


	return true;
}
