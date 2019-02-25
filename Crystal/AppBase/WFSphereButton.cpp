#include "WFSphereButton.h"

#include "imgui.h"

#include "../Math/Sphere3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFSphereButton::onShow()
{
	sphereButton.show();
	ImGui::InputInt("UNum", &unum);
	ImGui::InputInt("VNum", &vnum);
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFSphereButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(sphereButton.getValue(), unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), color, "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
