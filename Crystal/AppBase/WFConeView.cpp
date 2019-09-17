#include "WFConeView.h"

#include "../Math/Cone3d.h"
#include "../Shape/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFConeView::WFConeView(World* model, Canvas* canvas) :
	IOkCancelView("WFCone", model, canvas),
	cone("Cone"),
	attribute("Attribute"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
	add(&unum);
	add(&vnum);
	add(&cone);
	add(&attribute);
}

void WFConeView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cone.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getWorld()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Cone");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
