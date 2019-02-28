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
	torus.show();
	attribute.show();
}

void WFTorusButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(torus.getValue(), unum, vnum);
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attribute.getValue(), "Torus");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
