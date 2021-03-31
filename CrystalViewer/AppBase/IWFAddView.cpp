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

IWFAddView::IWFAddView(const std::string& name, Scene::World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	attributeView("WFAttribute"),
	nameView("Name", "WireFrame01")
{
	add(&attributeView);
	add(&nameView);
}

void IWFAddView::addWireFrame(const std::vector<Vector3dd>& positions, const std::vector<WireFrameEdge>& edges)
{
	WireFrameAttribute attr = attributeView.getValue();
	const auto& name = nameView.getValue();
	auto shape = std::make_unique<WireFrame>(positions, edges);
	auto newId = getWorld()->getNextSceneId();
	auto scene = new WireFrameScene(newId, name, std::move(shape), attr);
	getWorld()->getScenes()->addScene(scene);
	//getWorld()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}
