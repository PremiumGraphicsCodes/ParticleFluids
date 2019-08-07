#include "WFConeView.h"

#include "../Math/Cone3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFConeView::WFConeView(RootScene* model, Canvas* canvas) :
	IOkCancelView("WFCone", model, canvas),
	cone("Cone"),
	attribute("Attribute"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
}

void WFConeView::show()
{
	unum.show();
	vnum.show();
	cone.show();
	attribute.show();
	IOkCancelView::show();
}

void WFConeView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cone.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Cone");
	getRepository()->getObjects()->addScene(scene);
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
