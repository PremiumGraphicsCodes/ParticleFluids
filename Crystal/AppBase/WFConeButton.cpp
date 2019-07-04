#include "WFConeButton.h"

#include "imgui.h"

#include "../Math/Cone3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFConeButton::onShow()
{
	unum.show();
	vnum.show();
	cone.show();
	attribute.show();
}

void WFConeButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cone.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getModel()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Cone");
	getModel()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
