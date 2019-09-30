#include "WireFrameAddCommand.h"

#include "../Scene/WireFrameAttribute.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void WireFrameAddCommand::execute(World* world)
{
	const auto& lines = args.lines.getValue();
	WireFrameAttribute attr;
	attr.color = args.color.getValue();
	attr.width = args.lineWidth.getValue();
	const auto& name = args.name.getValue();
	if (args.isItem.getValue()) {
		auto scene = world->getObjectFactory()->createWireFrameScene(lines, attr, name);
		world->getObjects()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	else {
		auto scene = world->getItemFactory()->createWireFrameScene(lines, attr, name);
		world->getItems()->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	world->updateViewModel();

}
