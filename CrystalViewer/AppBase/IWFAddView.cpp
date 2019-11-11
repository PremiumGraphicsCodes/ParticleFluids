#include "IWFAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/WireFrameCreateLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IWFAddView::addWireFrame(const std::vector<Line3dd>& lines)
{
	const auto& attribute = attributeView.getValue();
	Command::Command command(WireFrameCreateLabels::WireFrameAddLabel);
	command.setArg(WireFrameCreateLabels::LinesLabel, lines);
	command.setArg(WireFrameCreateLabels::LineWidthLabel, attribute.width);
	command.setArg(WireFrameCreateLabels::ColorLabel, attribute.color);
	command.setArg(WireFrameCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}
