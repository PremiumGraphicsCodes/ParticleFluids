#include "FluidSceneUpdateCommand.h"

#include "PublicLabels/FluidSceneUpdateLabels.h"

#include "../CrystalPhysics/KFFluidScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

FluidSceneUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1),
	stiffness(::StiffnessLabel, 1.0f),
	density(::DensityLabel, 1.0f),
	viscosity(::ViscosityLabel, 1.0f),
	isBoundary(::IsBoundary, false),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&particleSystemId);
	add(&stiffness);
	add(&density);
	add(&viscosity);
	add(&isBoundary);
	add(&name);
}

FluidSceneUpdateCommand::Results::Results()
{
}

FluidSceneUpdateCommand::FluidSceneUpdateCommand() :
	ICommand(&args, &results)
{}

bool FluidSceneUpdateCommand::execute(World* world)
{
	auto fluidScene = world->getScenes()->findSceneById<KFFluidScene*>(args.id.getValue());

	fluidScene->clearParticles();
	fluidScene->clear();

	auto particles = world->getScenes()->findSceneById<IParticleSystemScene*>(args.particleSystemId.getValue());
	if (particles == nullptr) {
		return false;
	}
	const auto& positions = particles->getPositions();

	const auto radius = 1.0;
	const auto density = args.density.getValue();
	for (auto p : positions) {
		auto mp = new KFMacroParticle(radius, p);
		mp->distributePoints(3, 3, 3, density);
		fluidScene->addParticle(mp);
	}

	fluidScene->setName(args.name.getValue());
	fluidScene->setPressureCoe(args.stiffness.getValue());
	fluidScene->setViscosityCoe(args.viscosity.getValue());
	fluidScene->setBoundary(args.isBoundary.getValue());

	return true;
}