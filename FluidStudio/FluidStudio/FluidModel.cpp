#include "FluidModel.h"

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysicsCommand/FluidSceneUpdateCommand.h"

#include "CrystalScene/Command/XMLConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;
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

namespace {
	constexpr auto IdLabel = "Id";
	constexpr auto ParticleSystemIdLabel = "ParticleSystemId";
	constexpr auto StiffnessLabel = "Stiffness";
	constexpr auto ViscosityLabel = "Viscosity";
	constexpr auto HeatDiffuseLabel = "HeatDiffuse";
	constexpr auto DragForceLabel = "DragForce";
	constexpr auto DragHeatLabel = "DragHeat";
}

tinyxml2::XMLElement* FluidModel::toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent)
{
	tinyxml2::XMLElement* e = doc->NewElement("Fluid");
	e->SetAttribute("Name", this->name.c_str());
	parent->InsertEndChild(e);

	e->InsertEndChild(XMLConverter::toXML(doc, ::IdLabel, fluidId));
	e->InsertEndChild(XMLConverter::toXML(doc, ::ParticleSystemIdLabel, particleSystemId));
	e->InsertEndChild(XMLConverter::toXML(doc, ::StiffnessLabel, pressureCoe));
	e->InsertEndChild(XMLConverter::toXML(doc, ::ViscosityLabel, viscosityCoe));
	e->InsertEndChild(XMLConverter::toXML(doc, ::HeatDiffuseLabel, heatDiffuseCoe));
	e->InsertEndChild(XMLConverter::toXML(doc, ::DragForceLabel, dragForceCoe));
	e->InsertEndChild(XMLConverter::toXML(doc, ::DragHeatLabel, dragHeatCoe));

	return e;
}

bool FluidModel::fromXML(tinyxml2::XMLElement* parent)
{
	auto attr = parent->FirstAttribute();
	this->name = attr->Value();
	
	XMLConverter::fromXML(*parent, ::IdLabel, fluidId);
	XMLConverter::fromXML(*parent, ::ParticleSystemIdLabel, particleSystemId);
	XMLConverter::fromXML(*parent, ::StiffnessLabel, pressureCoe);
	XMLConverter::fromXML(*parent, ::ViscosityLabel, viscosityCoe);
	XMLConverter::fromXML(*parent, ::HeatDiffuseLabel, heatDiffuseCoe);
	XMLConverter::fromXML(*parent, ::DragForceLabel, dragForceCoe);
	XMLConverter::fromXML(*parent, ::DragHeatLabel, dragHeatCoe);

	return true;
};
