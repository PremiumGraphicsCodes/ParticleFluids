#include "WFBoxView.h"

#include "../Shape/WireFrameBuilder.h"
#include "../Scene/RootScene.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFBoxView::WFBoxView(RootScene* model, Canvas* canvas) :
	IOkCancelView("WFBox", model, canvas),
	box("Box"),
	attribute("Attribute")
{
}

void WFBoxView::show()
{
	box.show();
	attribute.show();
	IOkCancelView::show();
}

void WFBoxView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(box.getValue());
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Box");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}