#include "WFCylinderView.h"

#include "../Math/Cylinder3d.h"
#include "../Scene/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFCylinderView::WFCylinderView(World* model, Canvas* canvas) :
	IWFAddView("WFCylinder", model, canvas),
	cylinder("Cylinder"),
	unum("UNum", 12),
	vnum("VNum", 12)
{
	add(&cylinder);
	add(&unum);
	add(&vnum);
}

void WFCylinderView::onOk()
{
	WireFrameBuilder builder;
	builder.build(cylinder.getValue(), unum.getValue(), vnum.getValue());
	IWFAddView::addWireFrame(builder.getWireFrame());
}
