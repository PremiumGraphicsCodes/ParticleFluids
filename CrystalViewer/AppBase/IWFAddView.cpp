#include "IWFAddView.h"

#include "../../Crystal/Scene/WireFrameScene.h"

#include "../Command/Command.h"
#include "../Command/Public/WireFrameCreateLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IWFAddView::addWireFrame(const std::vector<Vector3dd>& positions, const std::vector<WireFrameEdge>& edges)
{
	const auto& attribute = attributeView.getValue();
	Command::Command command(WireFrameCreateLabels::WireFrameAddLabel);
	command.setArg(WireFrameCreateLabels::PositionsLabel, positions);
	command.setArg(WireFrameCreateLabels::EdgesLabel, edges);
	command.setArg(WireFrameCreateLabels::LineWidthLabel, attribute.width);
	command.setArg(WireFrameCreateLabels::ColorLabel, attribute.color);
	command.setArg(WireFrameCreateLabels::MatrixLabel, matrixView.getValue());
	command.setArg(WireFrameCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());

	getWorld()->updateViewModel();

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}
