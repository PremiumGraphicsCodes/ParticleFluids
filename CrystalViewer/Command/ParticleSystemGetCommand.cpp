#include "ParticleSystemGetCommand.h"

#include "../../Crystal/Scene/ParticleAttribute.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/ParticleSystemGetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ParticleSystemGetCommand::Args::Args() :
	psId(ParticleSystemGetLabels::PSIdLabel, -1),
	layer(ParticleSystemGetLabels::LayerLabel, 1)
{
	add(&psId);
	add(&layer);
}

ParticleSystemGetCommand::Results::Results() :
	positions(ParticleSystemGetLabels::PositionsLabel, {}),
	pointSize(ParticleSystemGetLabels::PointSizeLabel, 1.0f),
	color(ParticleSystemGetLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(ParticleSystemGetLabels::NameLabel, std::string(""))
{
	add(&positions);
	add(&pointSize);
	add(&color);
	add(&name);
}

std::string ParticleSystemGetCommand::getName()
{
	return ParticleSystemGetLabels::CommandNameLabel;
}

bool ParticleSystemGetCommand::execute(World* world)
{
	/*
	const auto& positions = args.positions.getValue();
	ParticleAttribute attr;
	attr.color = args.color.getValue();
	attr.size = args.pointSize.getValue();
	auto name = args.name.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto scene = new ParticleSystemScene(world->getNextSceneId(), name, std::move(shape));
	world->addScene(args.layer.getValue(), scene);
	//world->getRenderer()->getBuffer()->screen.add(scene, *world->getGLFactory());
	results.newId.setValue(scene->getId());
	//world->updateViewModel();
	*/
	return true;
}
