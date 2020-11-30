#include "ISolidAddView.h"

#include "../../Crystal/Scene/SolidScene.h"

#include "../Command/Command.h"
#include "../Command/Public/ShaderBuildLabels.h"
#include "../Command/Public/CameraLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

ISolidAddView::ISolidAddView(const std::string& name, Scene::World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
//	attributeView("WFAttribute"),
	nameView("Name", "WireFrame01")
{
	//add(&attributeView);
	add(&nameView);
}

void ISolidAddView::addSolid(const std::vector<Vector3dd>& positions, std::unique_ptr<Solid> solid)
{
	//WireFrameAttribute attr = attributeView.getValue();
	//const auto& name = nameView.getValue();
	//auto shape = std::make_unique<WireFrame>(positions, edges);
	auto newId = getWorld()->getNextSceneId();
	auto scene = new SolidScene(newId, name, std::move(solid));
	getWorld()->getScenes()->addScene(scene);
	//getWorld()->addScene(scene);


	Command::Command command;
	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
}
