#include "SolidCreateCommand.h"

#include "../../Crystal/Scene/SolidScene.h"

#include "Public/SolidCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SolidCreateCommand::Args::Args() :
	box(SolidCreateLabels::BoxLabel, Box3dd()),
	color(SolidCreateLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(SolidCreateLabels::NameLabel, std::string("")),
	layer(SolidCreateLabels::LayerLabel, 1)
{
	add(&box);
	add(&color);
	add(&name);
	add(&layer);
}

SolidCreateCommand::Results::Results() :
	newId(SolidCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string SolidCreateCommand::getName()
{
	return SolidCreateLabels::ParticleSystemAddLabel;
}

bool SolidCreateCommand::execute(World* world)
{
	const auto& box = args.box.getValue();
	const auto color = args.color.getValue();
	auto name = args.name.getValue();
	auto solid3d = std::make_unique<Crystal::Math::Box3dd>();
	(*solid3d) = box;
	std::unique_ptr< Crystal::Shape::Solid > solid = std::make_unique<Crystal::Shape::Solid>((std::move(solid3d)));
	auto scene = new SolidScene(world->getNextSceneId(), name, std::move(solid));
	world->addScene(args.layer.getValue(), scene);
	results.newId.setValue(scene->getId());
	return true;
}
