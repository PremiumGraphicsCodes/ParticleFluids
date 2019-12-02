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
	layer(ParticleSystemCreateLabels::LayerLabel, 1)
{
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
	add(&layer);
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
	auto scene = world->getSceneFactory()->createParticleSystemScene(positions, attr, name);
	world->addScene(args.layer.getValue(), scene);
	results.newId.setValue(scene->getId());
	world->updateViewModel();
}
