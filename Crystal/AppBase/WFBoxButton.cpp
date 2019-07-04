#include "WFBoxButton.h"

#include "imgui.h"

#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFBoxButton::onShow()
{
	box.show();
	attribute.show();
}

void WFBoxButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(box.getValue());
	auto scene = getModel()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Box");
	getModel()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void WFBoxButton::onCancel()
{
}
