#include "WireFrameAddCommand.h"

#include "../../Crystal/Scene/WireFrameAttribute.h"
#include "../../Crystal/Scene/WireFrameScene.h"

#include "Public/WireFrameAddLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

WireFrameAddCommand::Args::Args() :
	lines(WireFrameAddLabels::LinesLabel, {}),
	lineWidth(WireFrameAddLabels::LineWidthLabel, 1.0f),
	color(WireFrameAddLabels::ColorLabel, Graphics::ColorRGBAf(1, 1, 1, 1)),
	name(WireFrameAddLabels::NameLabel, std::string("")),
	isItem(WireFrameAddLabels::IsItemLabel, false)
{
	add(&lines);
	add(&lineWidth);
	add(&color);
	add(&name);
	add(&isItem);
}

WireFrameAddCommand::Results::Results() :
	newId(WireFrameAddLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string WireFrameAddCommand::getName()
{
	return WireFrameAddLabels::WireFrameAddLabel;
}

void WireFrameAddCommand::execute(World* world)
{
	const auto& lines = args.lines.getValue();
	WireFrameAttribute attr;
	attr.color = args.color.getValue();
	attr.width = args.lineWidth.getValue();
	const auto& name = args.name.getValue();
	if (args.isItem.getValue()) {
		auto scene = world->getItemFactory()->createWireFrameScene(lines, attr, name);
		world->getItems()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	else {
		auto scene = world->getObjectFactory()->createWireFrameScene(lines, attr, name);
		world->getObjects()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	world->updateViewModel();

}
