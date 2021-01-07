#include "VDBParticleSystemCreateCommand.h"

#include "../../CrystalVDB/VDBConverter/VDBParticleSystemScene.h"

#include "PublicLabels/VDBParticleSystemCreateLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::VDB;

VDBParticleSystemCreateCommand::Args::Args() :
	positions(::PositionsLabel, {})
{
	add(&positions);
}

VDBParticleSystemCreateCommand::Results::Results() :
	newId(::NewVDBPSIdLabel, -1)
{
	add(&newId);
}

std::string VDBParticleSystemCreateCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBParticleSystemCreateCommand::execute(World* world)
{
	auto mesh = new VDBParticleSystemScene(world->getNextSceneId(), "VDBPS");
	world->addScene(1, mesh);
	results.newId.setValue(mesh->getId());

	return true;
}
