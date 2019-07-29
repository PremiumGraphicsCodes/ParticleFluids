#include "WFCylinderView.h"

#include "../Math/Cylinder3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(Repository* model, Canvas* canvas) :
	IPanel("WFCylinder", model, canvas),
	cylinder("Cylinder"),
	attribute("Attribute"),
	unum("UNum", 12),
	vnum("VNum", 12),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void WFCylinderView::show()
{
	cylinder.show();
	unum.show();
	vnum.show();
	attribute.show();
}

void WFCylinderView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cylinder.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
