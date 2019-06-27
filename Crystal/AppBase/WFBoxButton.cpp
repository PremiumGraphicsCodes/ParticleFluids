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
	getModel()->getObjects()->getFactory()->addWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Box");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void WFBoxButton::onCancel()
{
}
