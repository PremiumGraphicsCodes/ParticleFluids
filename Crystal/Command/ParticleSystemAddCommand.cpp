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
	if (args.isItem.getValue()) {
		auto scene = world->getItemFactory()->createParticleSystemScene(positions, attr, name);
		world->getItems()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	else {
		auto scene = world->getObjectFactory()->createParticleSystemScene(positions, attr, name);
		world->getObjects()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	world->updateViewModel();

}
