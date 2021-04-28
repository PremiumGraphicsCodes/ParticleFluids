#include "EmitterSceneUpdateCommand.h"

#include "PublicLabels/EmitterSceneUpdateLabels.h"

#include "../CrystalPhysics/KFFluidEmitterScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string EmitterSceneUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

EmitterSceneUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1),
	particleRadius(::ParticleRadiusLabel, 0.5f),
	stiffness(::StiffnessLabel, 1.0f),
	density(::DensityLabel, 1.0f),
	viscosity(::ViscosityLabel, 1.0f),
	startStep(::StartStepLabel, 0),
	endStep(::EndStepLabel, 100),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&particleSystemId);
	add(&particleRadius);
	add(&stiffness);
	add(&density);
	add(&viscosity);
	add(&startStep);
	add(&endStep);
	add(&name);
}

EmitterSceneUpdateCommand::Results::Results()
{
}

EmitterSceneUpdateCommand::EmitterSceneUpdateCommand() :
	ICommand(&args, &results)
{}

bool EmitterSceneUpdateCommand::execute(World* world)
{
	auto fluidScene = world->getScenes()->findSceneById<KFFluidEmitterScene*>(args.id.getValue());

	fluidScene->clearParticles();
	fluidScene->clear();

	fluidScene->setName(args.name.getValue());
	fluidScene->setPressureCoe(args.stiffness.getValue());
	fluidScene->setViscosityCoe(args.viscosity.getValue());

	fluidScene->setStartEnd(args.startStep.getValue(), args.endStep.getValue());

	const auto psId = args.particleSystemId.getValue();
	if (psId > 0) {
		auto particles = world->getScenes()->findSceneById<IParticleSystemScene*>(psId);
		if (particles == nullptr) {
			return false;
		}
		const auto& positions = particles->getPositions();
		const auto radius = args.particleRadius.getValue();
		const auto density = args.density.getValue();
		for (const auto& p : positions) {
			auto mp = new KFMacroParticle(radius, p);
			mp->distributePoints(3, 3, 3, density);
			fluidScene->addParticle(mp);
		}
	}

	return true;
}