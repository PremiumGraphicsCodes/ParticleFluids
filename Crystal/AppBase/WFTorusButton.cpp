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
	auto scene = getModel()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Torus");
	getModel()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
