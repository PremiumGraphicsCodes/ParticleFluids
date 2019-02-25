#include "WFConeButton.h"

#include "imgui.h"

#include "../Math/Cone3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFConeButton::onShow()
{
	ImGui::InputInt("UNum", &unum);
	ImGui::InputInt("VNum", &vnum);
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputDouble("Radius", &radius);
	ImGui::InputDouble("Height", &height);
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFConeButton::onOk()
{
	const Cone3d cone(center, radius, height);
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cone, unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Cone");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
