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
	isItem(WireFrameCreateLabels::IsItemLabel, false)
{
	add(&positions);
	add(&edges);
	add(&lineWidth);
	add(&color);
	add(&name);
	add(&isItem);
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

void WireFrameCreateCommand::execute(World* world)
{
	const auto& positions = args.positions.getValue();
	const auto& edges = args.edges.getValue();
	WireFrameAttribute attr;
	attr.color = args.color.getValue();
	attr.width = args.lineWidth.getValue();
	const auto& name = args.name.getValue();
	WireFrame* shape = new WireFrame(positions, edges);
	if (args.isItem.getValue()) {
		auto scene = world->getSceneFactory()->createWireFrameScene(shape, attr, name);
		world->getItems()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	else {
		auto scene = world->getSceneFactory()->createWireFrameScene(shape, attr, name);
		world->getObjects()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	world->updateViewModel();

}
