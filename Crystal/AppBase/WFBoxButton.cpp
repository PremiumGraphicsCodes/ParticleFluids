#include "WFBoxButton.h"

#include "imgui.h"

#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFBoxButton::onShow()
{
	boxButton.show();
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFBoxButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(boxButton.getValue());
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Box");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void WFBoxButton::onCancel()
{
}
