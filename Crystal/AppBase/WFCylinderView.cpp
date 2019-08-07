#include "WFCylinderView.h"

#include "../Math/Cylinder3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(World* model, Canvas* canvas) :
	IOkCancelView("WFCylinder", model, canvas),
	cylinder("Cylinder"),
	attribute("Attribute"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
}

void WFCylinderView::show()
{
	cylinder.show();
	unum.show();
	vnum.show();
	attribute.show();
	IOkCancelView::show();
}

void WFCylinderView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cylinder.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getRepository()->getObjects()->addScene(scene);
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
