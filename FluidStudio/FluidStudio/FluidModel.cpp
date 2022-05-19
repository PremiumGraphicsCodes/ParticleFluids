#include "FluidModel.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/FluidSceneUpdateCommand.h"


using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;
using namespace PG::FS;

void FluidModel::create(World* world)
{
	auto fluidScene = new MVPFluidScene(world->getNextSceneId(), "MVPFluid");

	this->pressureCoe = 500.0f;
	this->viscosityCoe = 50.0f;
	this->heatDiffuseCoe = 0.0f;
	this->dragForceCoe = 0.0f;
	this->dragHeatCoe = 0.0;


	fluidScene->getPresenter()->createView(world->getRenderer());
	world->getScenes()->addScene(fluidScene);


	this->fluidId = fluidScene->getId();

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

tinyxml2::XMLElement* FluidModel::toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent)
{
	tinyxml2::XMLElement* code2 = doc->NewElement("Fluid");
	code2->SetAttribute("Name", this->name.c_str());
	parent->InsertEndChild(code2);

	tinyxml2::XMLElement* idElem = doc->NewElement("Id");
	{
		auto text = doc->NewText(std::to_string(fluidId).c_str());
		idElem->InsertEndChild(text);
		code2->InsertEndChild(idElem);
	}

	tinyxml2::XMLElement* psIdElem = doc->NewElement("ParticleSystemId");
	{
		auto text = doc->NewText(std::to_string(particleSystemId).c_str());
		psIdElem->InsertEndChild(text);
		code2->InsertEndChild(psIdElem);
	}
	return code2;
}
