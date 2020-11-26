#include "IWFAddView.h"

#include "../../Crystal/Scene/WireFrameScene.h"

#include "../Command/Command.h"
#include "../Command/Public/ShaderBuildLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

void IWFAddView::addWireFrame(const std::vector<Vector3dd>& positions, const std::vector<WireFrameEdge>& edges)
{
	WireFrameAttribute attr = attributeView.getValue();
	const auto& name = nameView.getValue();
	auto shape = std::make_unique<WireFrame>(positions, edges);
	auto newId = getWorld()->getNextSceneId();
	auto scene = new WireFrameScene(newId, name, std::move(shape), attr);
	getWorld()->getScenes()->addScene(scene);
	//getWorld()->addScene(scene);


	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}
