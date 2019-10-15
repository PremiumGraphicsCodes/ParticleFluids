#include "IWFAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/WireFrameAddLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IWFAddView::addWireFrame(const std::vector<Line3dd>& lines)
{
	const auto& attribute = attributeView.getValue();
	Command::Command command(::WireFrameAddLabel);
	command.setArg(::LinesLabel, lines);
	command.setArg(::LineWidthLabel, attribute.width);
	command.setArg(::ColorLabel, attribute.color);
	command.setArg(::NameLabel, nameView.getValue());
	command.execute(getWorld());

	command.create(::CameraFitCommandLabel);
	command.execute(getWorld());
}
