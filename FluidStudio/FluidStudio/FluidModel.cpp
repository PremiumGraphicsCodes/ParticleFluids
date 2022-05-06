#include "FluidModel.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/FluidSceneUpdateCommand.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace Crystal::UI;

void FluidModel::create(World* world)
{
	auto fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");

	this->pressureCoe = 500.0f;

	auto ps = std::make_unique<Crystal::Shape::ParticleSystem<ParticleAttribute>>();
	{
		const auto radius = 1.0;
		const auto length = radius * 0.5;
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < 20; ++j) {
				for (int k = 0; k < 20; ++k) {
					//auto mp = new MVPVolumeParticle(radius*2.0, Vector3dd(i * length, j * length, k * length));
					auto p = Vector3dd(i * length, j * length, k * length);
					ParticleAttribute attr;
					attr.size = 0.25f;
					ps->add(p, attr);
				}
			}
		}
	}
	auto psScene = new ParticleSystemScene(world->getNextSceneId(), "", std::move(ps));


	fluidScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(fluidScene);

	psScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(psScene);

	this->fluidId = fluidScene->getId();
	this->particleSystemId = psScene->getId();

	//reset(world);
}

void FluidModel::reset(World* world)
{
	FluidSceneUpdateCommand::Args args;
	args.id.setValue(this->fluidId);
	args.particleSystemId.setValue(this->particleSystemId);
	args.stiffness.setValue(this->pressureCoe);
	args.viscosity.setValue(this->viscosityCoe);
	args.heatDiffuseCoe.setValue(this->heatDiffuseCoe);
	args.dragForceCoe.setValue(this->dragForceCoe);
	args.dragHeatCoe.setValue(this->dragHeatCoe);
	FluidSceneUpdateCommand command(args);
	command.execute(world);
}
