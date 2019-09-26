#include "ParticleSystemAddCommand.h"

#include "../Scene/ParticleAttribute.h"
#include "../Scene/ParticleSystemScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void ParticleSystemAddCommand::execute(World* world)
{
	const auto positions = args.positions.getValue();
	ParticleAttribute attr;
	attr.color = args.color.getValue();
	attr.size = args.pointSize.getValue();
	auto name = args.name.getValue();
	auto scene = world->getObjectFactory()->createParticleSystemScene(positions, attr, name);

	world->getObjects()->addScene(scene);
	world->updateViewModel();

	results.newId.setValue(scene->getId());
}
