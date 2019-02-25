#include "WFSphereButton.h"

#include "imgui.h"

#include "../Math/Sphere3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFSphereButton::onShow()
{
	ImGui::InputInt("UNum", &unum);
	ImGui::InputInt("VNum", &vnum);
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputFloat("Radius", &radius);
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFSphereButton::onOk()
{
	const Sphere3d sphere(center, radius);
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(sphere, unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
