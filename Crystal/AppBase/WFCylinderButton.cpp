#include "WFCylinderButton.h"

#include "../Math/Cylinder3d.h"
#include "../Shape/WireFrameBuilder.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFCylinderButton::onShow()
{
	ImGui::InputInt("UNum", &unum);
	ImGui::InputInt("VNum", &vnum);
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputDouble("Radius", &radius);
	ImGui::InputDouble("Height", &radius);
	attributeButton.show();
}

void WFCylinderButton::onOk()
{
	const Cylinder3d sphere(radius, height, center);
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(sphere, unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attributeButton.getValue(), "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
