#include "WFSphereButton.h"

#include "imgui.h"

#include "../Math/Sphere3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void WFSphereButton::onShow()
{
	sphere.show();
	unum.show();
	vnum.show();
	attribute.show();
}

void WFSphereButton::onOk()
{
	WireFrameBuilder builder;
	builder.build(sphere.getValue(), unum.getValue(), vnum.getValue());
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}
