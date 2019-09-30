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
	auto scene = world->getObjectFactory()->createWireFrameScene(lines, attr, name);

	world->getObjects()->addScene(scene);
	world->updateViewModel();

	results.newId.setValue(scene->getId());
}
