#include "WFRayButton.h"

#include "imgui.h"

#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

void WFRayButton::onShow()
{
	ray.show();
	attribute.show();
}

void WFRayButton::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(ray.getValue(), length.getValue());
	getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attribute.getValue(), "Ray");
	getCanvas()->setViewModel(getModel()->toViewModel());
	getCanvas()->fitCamera(getModel()->getBoundingBox());
}

void WFRayButton::onCancel()
{
}
