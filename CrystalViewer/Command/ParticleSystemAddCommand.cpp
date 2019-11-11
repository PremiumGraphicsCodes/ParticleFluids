#include "ParticleSystemAddCommand.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/ParticleSystemAddLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ParticleSystemAddCommand::Args::Args() :
	positions(ParticleSystemAddLabels::PositionsLabel, {}),
	pointSize(ParticleSystemAddLabels::PointSizeLabel, 1.0f),
	color(ParticleSystemAddLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(ParticleSystemAddLabels::NameLabel, std::string("")),
	isItem(ParticleSystemAddLabels::IsItemLabel, false)
{
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
	add(&isItem);
}

ParticleSystemAddCommand::Results::Results() :
	newId(ParticleSystemAddLabels::NewIdLabel, -1)
{
	add(&newId);
}


std::string ParticleSystemAddCommand::getName()
{
	return ParticleSystemAddLabels::ParticleSystemAddLabel;
}

void ParticleSystemAddCommand::execute(World* world)
{
	const auto& positions = args.positions.getValue();
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
