#include "WFBoxView.h"

#include "../Shape/WireFrameBuilder.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

WFBoxView::WFBoxView(Repository* model, Canvas* canvas) :
	IPanel("WFBox", model, canvas),
	box("Box"),
	attribute("Attribute"),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void WFBoxView::show()
{
	box.show();
	attribute.show();
	ok.show();
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