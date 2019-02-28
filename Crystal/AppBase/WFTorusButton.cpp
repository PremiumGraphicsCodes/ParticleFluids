#include "WFTorusButton.h"

#include "imgui.h"

#include "../Math/Torus3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFTorusButton::onShow()
{
	unum.show();
	vnum.show();
	torus.show();
	attribute.show();
}

void WFTorusButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(torus.getValue(), unum.getValue(), vnum.getValue());
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attribute.getValue(), "Torus");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
