#include "WFCylinderView.h"

#include "../Math/Cylinder3d.h"
#include "../Scene/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

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
	add(&cylinder);
	add(&unum);
	add(&vnum);
	add(&attribute);
}

void WFCylinderView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cylinder.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getWorld()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Sphere");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
