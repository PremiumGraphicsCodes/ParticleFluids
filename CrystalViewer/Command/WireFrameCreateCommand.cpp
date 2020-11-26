#include "WireFrameCreateCommand.h"

#include "../../Crystal/Scene/WireFrameAttribute.h"
#include "../../Crystal/Scene/WireFrameScene.h"

#include "Public/WireFrameCreateLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

WireFrameCreateCommand::Args::Args() :
	positions(WireFrameCreateLabels::PositionsLabel, {}),
	edges(WireFrameCreateLabels::EdgesLabel, {}),
	lineWidth(WireFrameCreateLabels::LineWidthLabel, 1.0f),
	color(WireFrameCreateLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(WireFrameCreateLabels::NameLabel, std::string("")),
	layer(WireFrameCreateLabels::LayerLabel, 1)
{
	add(&positions);
	add(&edges);
	add(&lineWidth);
	add(&color);
	add(&name);
	add(&layer);
}

WireFrameCreateCommand::Results::Results() :
	newId(WireFrameCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string WireFrameCreateCommand::getName()
{
	return WireFrameCreateLabels::WireFrameAddLabel;
}

bool WireFrameCreateCommand::execute(World* world)
{
	const auto& positions = args.positions.getValue();
	const auto& edges = args.edges.getValue();
	WireFrameAttribute attr;
	attr.color = args.color.getValue();
	attr.width = args.lineWidth.getValue();
	const auto& name = args.name.getValue();
	auto shape = std::make_unique<WireFrame>(positions, edges);
	auto newId = world->getNextSceneId();
	auto scene = new WireFrameScene(newId, name, std::move(shape), attr);
	world->getScenes()->addScene(scene);
	world->addScene(args.layer.getValue(), scene);
	results.newId.setValue(scene->getId());
	//world->updateViewModel();
	return true;
}
