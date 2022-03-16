#include "EmitterSceneUpdateCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "EmitterSceneUpdateCommand";
	PublicLabel IdLabel = "Id";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel StiffnessLabel = "Stiffness";
	PublicLabel ViscosityLabel = "Viscosity";
	PublicLabel InitialVelocityLabel = "InitialVelocity";
	PublicLabel DensityLabel = "Density";
	PublicLabel NameLabel = "Name";
	PublicLabel StartStepLabel = "StartStep";
	PublicLabel EndStepLabel = "EndStep";
	PublicLabel IntervalLabel = "Interval";
}


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
	initialVelocity(::InitialVelocityLabel, Vector3df(0,0,0)),
	startStep(::StartStepLabel, 0),
	endStep(::EndStepLabel, 100),
	interval(::IntervalLabel, 10),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&particleSystemId);
	add(&particleRadius);
	add(&stiffness);
	add(&density);
	add(&viscosity);
	add(&initialVelocity);
	add(&startStep);
	add(&endStep);
	add(&interval);
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
	auto emitterScene = world->getScenes()->findSceneById<MVPFluidEmitterScene*>(args.id.getValue());

	emitterScene->clearSources();
	emitterScene->clearParticles();
	emitterScene->clear();

	emitterScene->setName(args.name.getValue());
	emitterScene->setPressureCoe(args.stiffness.getValue());
	emitterScene->setViscosityCoe(args.viscosity.getValue());
	emitterScene->setInitialVelocity(args.initialVelocity.getValue());

	emitterScene->setStartEnd(args.startStep.getValue(), args.endStep.getValue());
	emitterScene->setInterval(args.interval.getValue());

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
			emitterScene->addSource(Sphere3dd(p, radius));
		}
	}

	return true;
}