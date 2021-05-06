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
	auto emitterScene = world->getScenes()->findSceneById<KFFluidEmitterScene*>(args.id.getValue());

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
			emitterScene->addSource(Sphere3d(p, radius));
		}
	}

	return true;
}