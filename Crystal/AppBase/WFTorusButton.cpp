#include "WFTorusButton.h"

#include "imgui.h"

#include "../Math/Torus3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFTorusButton::onShow()
{
	ImGui::InputInt("UNum", &unum);
	ImGui::InputInt("VNum", &vnum);
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputDouble("BigRadius", &bigRadius);
	ImGui::InputDouble("SmallRadius", &smallRadius);
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFTorusButton::onOk()
{
	const Torus3d torus(center, bigRadius, smallRadius);
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(torus, unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Torus");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
