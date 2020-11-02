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
	stiffness(::StiffnessLabel, 1.0f),
	viscosity(::ViscosityLabel, 1.0f),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&particleSystemId);
	add(&stiffness);
	add(&viscosity);
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
	const auto radius = 1.0;
	for (auto p : positions) {
		auto mp = new KFMacroParticle(radius, p);
		mp->distributePoints(3, 3, 3, 1.0f);
		fluidScene->addParticle(mp);
	}

	//fluidScene->addParticle()
	fluidScene->setPressureCoe(args.stiffness.getValue());
	fluidScene->setViscosityCoe(args.viscosity.getValue());
	world->getScenes()->addScene(fluidScene);

	results.newId.setValue(fluidScene->getId());

	return true;
}