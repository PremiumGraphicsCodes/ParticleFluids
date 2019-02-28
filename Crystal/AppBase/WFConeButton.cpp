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
	coneButton.show();
	attributeButton.show();
}

void WFConeButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(coneButton.getValue(), unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attributeButton.getValue(), "Cone");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
