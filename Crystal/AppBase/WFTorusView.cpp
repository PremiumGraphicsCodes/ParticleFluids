#include "WFTorusView.h"

#include "../Math/Torus3d.h"
#include "../Shape/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFTorusView::WFTorusView(World* model, Canvas* canvas) :
	IPanel("WFTorus", model, canvas),
	torus("Torus"),
	attribute("Attribute"),
	unum("UNum", 24),
	vnum("VNum", 12)
{
	add(&unum);
	add(&vnum);
	add(&torus);
	add(&attribute);
}

void WFTorusView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(torus.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getWorld()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Torus");
	getWorld()->getObjects()->addScene(scene);
	getWorld()->updateViewModel();
	getCanvas()->fitCamera(getWorld()->getBoundingBox());
}
