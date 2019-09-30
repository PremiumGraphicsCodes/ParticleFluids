#include "IWFAddView.h"

#include "../Command/Command.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IWFAddView::addWireFrame(const std::vector<Line3dd>& lines)
{
	const auto& attribute = attributeView.getValue();
	Command::Command command("WireFrameAdd");
	command.setArg("Lines", lines);
	command.setArg("LineWidth", attribute.width);
	command.setArg("Color", attribute.color);
	command.setArg("Name", nameView.getValue());
	command.execute(getWorld());

	command.create("CameraFit");
	command.execute(getWorld());
}
