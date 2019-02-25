#include "WFBoxButton.h"

#include "imgui.h"

#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFBoxButton::onShow()
{
	ImGui::InputFloat3("Min", &min[0]);
	ImGui::InputFloat3("Max", &max[0]);
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFBoxButton::onOk()
{
	const Box3d box(min, max);
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(box);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Box");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void WFBoxButton::onCancel()
{
}
