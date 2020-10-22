#include "FluidSceneCreateCommand.h"

#include "PublicLabels/FluidSceneCreateLabels.h"

#include "../CrystalPhysics/KFFluidScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

FluidSceneCreateCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&particleSystemId);
	add(&name);
}

FluidSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

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
	world->getScenes()->addScene(fluidScene);

	results.newId.setValue(fluidScene->getId());

	return true;
}