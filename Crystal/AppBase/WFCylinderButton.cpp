#include "WFCylinderButton.h"

#include "../Math/Cylinder3d.h"
#include "../Shape/WireFrameBuilder.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFCylinderButton::onShow()
{
	cylinder.show();
	ImGui::InputInt("UNum", &unum);
	ImGui::InputInt("VNum", &vnum);
	attribute.show();
}

void WFCylinderButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cylinder.getValue(), unum, vnum);
	getModel()->getObjects()->getFactory()->addWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
