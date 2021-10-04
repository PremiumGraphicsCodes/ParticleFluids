#include "WireFrameCreateCommand.h"

#include "../Scene/WireFrameAttribute.h"
#include "../Scene/WireFrameScene.h"

#include "PublicLabel.h"

namespace WireFrameCreateLabels
{
	PublicLabel WireFrameAddLabel = "WireFrameAdd";
	PublicLabel PositionsLabel = "Positions";
	PublicLabel EdgesLabel = "Edges";
	PublicLabel LineWidthLabel = "LineWidth";
	PublicLabel ColorLabel = "Color";
	PublicLabel NameLabel = "Name";
	PublicLabel LayerLabel = "Layer";
	PublicLabel NewIdLabel = "NewId";
}

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
