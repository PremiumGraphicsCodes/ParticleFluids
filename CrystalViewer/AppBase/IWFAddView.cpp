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
	Command::Command command(WireFrameAddLabels::WireFrameAddLabel);
	command.setArg(WireFrameAddLabels::LinesLabel, lines);
	command.setArg(WireFrameAddLabels::LineWidthLabel, attribute.width);
	command.setArg(WireFrameAddLabels::ColorLabel, attribute.color);
	command.setArg(WireFrameAddLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}
