#include "ParticleSystemCreateCommand.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/ParticleSystemCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ParticleSystemCreateCommand::Args::Args() :
	positions(ParticleSystemCreateLabels::PositionsLabel, {}),
	pointSize(ParticleSystemCreateLabels::PointSizeLabel, 1.0f),
	color(ParticleSystemCreateLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(ParticleSystemCreateLabels::NameLabel, std::string("")),
	layer(ParticleSystemCreateLabels::LayerLabel, 1),
	matrix(ParticleSystemCreateLabels::MatrixLabel, Identity())
{
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
	add(&layer);
	add(&matrix);
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

bool ParticleSystemCreateCommand::execute(World* world)
{
	const auto& positions = args.positions.getValue();
	ParticleAttribute attr;
	attr.color = args.color.getValue();
	attr.size = args.pointSize.getValue();
	auto name = args.name.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto scene = new ParticleSystemScene(world->getNextSceneId(), name, std::move(shape));
	scene->setMatrix(args.matrix.getValue());
	world->addScene(args.layer.getValue(), scene);
	//world->getRenderer()->getBuffer()->screen.add(scene, *world->getGLFactory());
	results.newId.setValue(scene->getId());
	//world->updateViewModel();
	return true;
}
