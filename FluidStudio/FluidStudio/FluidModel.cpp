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
	tinyxml2::XMLElement* e = doc->NewElement("Fluid");
	e->SetAttribute("Name", this->name.c_str());
	parent->InsertEndChild(e);

	{
		auto elem = doc->NewElement("Id");
		auto text = doc->NewText(std::to_string(fluidId).c_str());
		elem->InsertEndChild(text);
		e->InsertEndChild(elem);
	}

	{
		auto elem = doc->NewElement("ParticleSystemId");
		auto text = doc->NewText(std::to_string(particleSystemId).c_str());
		elem->InsertEndChild(text);
		e->InsertEndChild(elem);
	}

	{
		auto elem = doc->NewElement("Stiffness");
		auto text = doc->NewText(std::to_string(this->pressureCoe).c_str());
		elem->InsertEndChild(text);
		e->InsertEndChild(elem);
	}

	{
		auto elem = doc->NewElement("Viscosity");
		auto text = doc->NewText(std::to_string(this->viscosityCoe).c_str());
		elem->InsertEndChild(text);
		e->InsertEndChild(elem);
	}

	{
		auto elem = doc->NewElement("HeatDiffuse");
		auto text = doc->NewText(std::to_string(this->heatDiffuseCoe).c_str());
		elem->InsertEndChild(text);
		e->InsertEndChild(elem);
	}
	return e;
}
