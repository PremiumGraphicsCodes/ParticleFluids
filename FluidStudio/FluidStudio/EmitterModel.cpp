#include "EmitterModel.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/EmitterSceneUpdateCommand.h"

using namespace PG::FS;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

EmitterModel::EmitterModel() :
	name("Emitter01"),
	fluidId(-1),
	particleSystemId(-1),
	pressureCoe(500.0f),
	viscosityCoe(50.0f),
	heatDiffuseCoe(0.0f),
	dragForceCoe(0.0f),
	dragHeatCoe(0.0f),
	temperature(300.0f),
	lifeLimit(500),
	initialVelocity(0.0f, 0.0f, 0.0f)
{}

void EmitterModel::create(World* world)
{
	auto fluidScene = new MVPFluidEmitterScene(world->getNextSceneId(), "MVPEmitter");

	fluidScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(fluidScene);

	this->fluidId = fluidScene->getId();
}

void EmitterModel::reset(World* world)
{
	EmitterSceneUpdateCommand::Args args;
	args.id.setValue(this->fluidId);
	args.particleSystemId.setValue(this->particleSystemId);
	args.stiffness.setValue(this->pressureCoe);
	args.viscosity.setValue(this->viscosityCoe);
	args.heatDiffuseCoe.setValue(this->heatDiffuseCoe);
	args.dragForceCoe.setValue(this->dragForceCoe);
	args.dragHeatCoe.setValue(this->dragHeatCoe);
	args.initialVelocity.setValue(this->initialVelocity);
	args.temperature.setValue(this->temperature);
	args.lifeLimit.setValue(this->lifeLimit);
	EmitterSceneUpdateCommand command(args);
	command.execute(world);
}

tinyxml2::XMLElement* EmitterModel::toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent)
{
	return nullptr;
}
