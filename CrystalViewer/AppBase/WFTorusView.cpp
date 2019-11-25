#include "WFTorusView.h"

#include "../../Crystal/Math/Torus3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFTorusView::WFTorusView(World* model, Canvas* canvas) :
	IWFAddView("WFTorus", model, canvas),
	torus("Torus"),
	unum("UNum", 24),
	vnum("VNum", 12)
{
	add(&unum);
	add(&vnum);
	add(&torus);
}

void WFTorusView::onOk()
{
	WireFrameBuilder builder;
	builder.build(torus.getValue(), unum.getValue(), vnum.getValue());
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}
