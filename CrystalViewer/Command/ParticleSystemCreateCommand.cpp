#include "ParticleSystemCreateCommand.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/ParticleSystemCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ParticleSystemCreateCommand::Args::Args() :
	positions(ParticleSystemCreateLabels::PositionsLabel, {}),
	pointSize(ParticleSystemCreateLabels::PointSizeLabel, 1.0f),
	color(ParticleSystemCreateLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(ParticleSystemCreateLabels::NameLabel, std::string("")),
	isItem(ParticleSystemCreateLabels::IsItemLabel, false)
{
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
	add(&isItem);
}

ParticleSystemCreateCommand::Results::Results() :
	newId(ParticleSystemCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}


std::string ParticleSystemCreateCommand::getName()
{
	return ParticleSystemCreateLabels::ParticleSystemAddLabel;
}

void ParticleSystemCreateCommand::execute(World* world)
{
	const auto& positions = args.positions.getValue();
	ParticleAttribute attr;
	attr.color = args.color.getValue();
	attr.size = args.pointSize.getValue();
	auto name = args.name.getValue();
	if (args.isItem.getValue()) {
		auto scene = world->getSceneFactory()->createParticleSystemScene(positions, attr, name);
		world->getItems()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	else {
		auto scene = world->getSceneFactory()->createParticleSystemScene(positions, attr, name);
		world->getObjects()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	world->updateViewModel();
}
