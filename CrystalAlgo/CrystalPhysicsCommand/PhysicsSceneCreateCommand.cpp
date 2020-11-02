#include "PhysicsSceneCreateCommand.h"

//#include "PublicLabels/FluidSceneCreateLabels.h"

#include "../CrystalPhysics/KFFluidScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSceneCreateCommand::getName()
{
	return "PhysicsSceneCreate";
}

PhysicsSceneCreateCommand::Args::Args() :
	fluidSceneIds("FluidSceneIds", {}),
	name("Name", std::string("FluidScene"))
{
	add(&name);
}

PhysicsSceneCreateCommand::Results::Results() :
	newId("NewId", -1)
{
	add(&newId);
}

/*
FluidSceneCreateCommand::FluidSceneCreateCommand() :
	ICommand(&args, &results)
{}

bool FluidSceneCreateCommand::execute(World* world)
{
	auto particles = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (particles == nullptr) {
		return false;
	}
	const auto& positions = particles->getShape()->getPositions();

	auto fluidScene = new KFFluidScene(world->getNextSceneId(), args.name.getValue());
	fluidScene->setPressureCoe(args.stiffness.getValue());
	fluidScene->setViscosityCoe(args.viscosity.getValue());
	world->getScenes()->addScene(fluidScene);

	results.newId.setValue(fluidScene->getId());

	return true;
}
*/