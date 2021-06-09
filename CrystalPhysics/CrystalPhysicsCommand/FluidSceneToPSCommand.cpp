#include "FluidSceneToPSCommand.h"

#include "PublicLabels/FluidSceneToPSLabels.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneToPSCommand::getName()
{
	return ::CommandNameLabel;
}

FluidSceneToPSCommand::Args::Args() :
	fluidId(::FluidIdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1)
{
	add(&fluidId);
	add(&particleSystemId);
}

FluidSceneToPSCommand::Results::Results()
{
}

FluidSceneToPSCommand::FluidSceneToPSCommand() :
	ICommand(&args, &results)
{}

bool FluidSceneToPSCommand::execute(World* world)
{
	auto fluidScene = world->getScenes()->findSceneById<MVPFluidScene*>(args.fluidId.getValue());
	if (fluidScene == nullptr) {
		return false;
	}

	auto particleScene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (particleScene == nullptr) {
		return false;
	}
	auto& particles = particleScene->getShape()->getParticles();

	auto macroPositions = fluidScene->getParticles();
	for (int i = 0; i < macroPositions.size(); ++i) {
		particles[i]->moveTo(macroPositions[i]->getPosition());
	}

	return true;
}