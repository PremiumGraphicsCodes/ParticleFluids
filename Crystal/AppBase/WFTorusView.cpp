#include "WFTorusView.h"

#include "imgui.h"

#include "../Math/Torus3d.h"
#include "../Shape/WireFrameBuilder.h"

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
}

void WFTorusView::show()
{
	unum.show();
	vnum.show();
	torus.show();
	attribute.show();
}

void WFTorusView::onOk()
{
	Crystal::Shape::WireFrameBuilder builder;
	builder.build(torus.getValue(), unum.getValue(), vnum.getValue());
	auto scene = getRepository()->getObjectFactory()->createWireFrameScene(builder.getWireFrame(), attribute.getValue(), "Torus");
	getRepository()->getObjects()->addScene(scene);
	getRepository()->updateViewModel();
	getCanvas()->fitCamera(getRepository()->getBoundingBox());
}
