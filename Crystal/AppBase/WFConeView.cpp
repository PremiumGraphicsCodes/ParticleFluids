#include "WFConeView.h"

#include "../Math/Cone3d.h"
#include "../Scene/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFConeView::WFConeView(World* model, Canvas* canvas) :
	IWFAddView("WFCone", model, canvas),
	cone("Cone"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
	add(&unum);
	add(&vnum);
	add(&cone);
}

void WFConeView::onOk()
{
	WireFrameBuilder builder;
	builder.build(cone.getValue(), unum.getValue(), vnum.getValue());
	IWFAddView::addWireFrame(builder.getWireFrame());
}
