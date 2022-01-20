#include "FluidSceneUpdateCommand.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../CrystalPhysics/MVP/MVPParticleBuilder.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "FluidSceneUpdateCommand";
	PublicLabel IdLabel = "Id";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel StiffnessLabel = "Stiffness";
	PublicLabel ViscosityLabel = "Viscosity";
	PublicLabel VorticityLabel = "Vorticity";
	PublicLabel DensityLabel = "Density";
	PublicLabel IsBoundary = "IsBoundary";
	PublicLabel NameLabel = "Name";
}


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
	particleRadius(::ParticleRadiusLabel, 0.5f),
	stiffness(::StiffnessLabel, 1.0f),
	density(::DensityLabel, 1.0f),
	viscosity(::ViscosityLabel, 1.0f),
	vorticity(::VorticityLabel, 0.05f),
	isBoundary(::IsBoundary, false),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&particleSystemId);
	add(&particleRadius);
	add(&stiffness);
	add(&density);
	add(&viscosity);
	add(&vorticity);
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
	auto fluidScene = world->getScenes()->findSceneById<MVPFluidScene*>(args.id.getValue());

	fluidScene->clearParticles();
	fluidScene->clear();

	fluidScene->setName(args.name.getValue());
	fluidScene->setPressureCoe(args.stiffness.getValue());
	fluidScene->setViscosityCoe(args.viscosity.getValue());
	fluidScene->setViscosityCoe(args.vorticity.getValue());
	fluidScene->setBoundary(args.isBoundary.getValue());

	const auto psId = args.particleSystemId.getValue();
	if (psId > 0) {
		auto particles = world->getScenes()->findSceneById<IParticleSystemScene*>(psId);
		if (particles == nullptr) {
			return false;
		}
		const auto& positions = particles->getPositions();
		const auto radius = args.particleRadius.getValue();
		const auto density = args.density.getValue();
		MVPParticleBuilder builder;
		for (const auto& p : positions) {
			//auto mp = new MVPVolumeParticle(radius, p);
			//mp->addMassParticle();// distributePoints(3, 3, 3, density);
			//auto mp = builder.create(p, radius, 3, 3, 3, 1.0f);
			//fluidScene->addParticle(mp);
		}
	}

	return true;
}