#include "WFConeView.h"

#include "../Math/Cone3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

WFConeView::WFConeView(Repository* model, Canvas* canvas) :
	IPanel("WFCone", model, canvas),
	cone("Cone"),
	attribute("Attribute"),
	unum("UNum", 12),
	vnum("VNum", 12),
	ok("Ok")
{
	ok.setFunction([=]() { onOk(); });
}

void WFConeView::show()
{
	unum.show();
	vnum.show();
	cone.show();
	attribute.show();
	ok.show();
}

void WFConeView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(cone.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Cone");
	getRepository()->getObjects()->addScene(scene);
	getCanvas()->setViewModel(getRepository()->toViewModel());
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
