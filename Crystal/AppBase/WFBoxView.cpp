#include "WFBoxView.h"

#include "../Shape/WireFrameBuilder.h"
#include "../Scene/World.h"
#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFBoxView::WFBoxView(World* model, Canvas* canvas) :
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
	auto scene = getWorld()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Box");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}