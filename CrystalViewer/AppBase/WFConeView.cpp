#include "WFConeView.h"

#include "../../Crystal/Math/Cone3d.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/WireFrameScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

WFConeView::WFConeView(const std::string& name, World* world, Canvas* canvas) :
	IWFAddView(name, world, canvas),
	coneView("Cone"),
	unumView("UNum", 12),
	vnumView("VNum", 12)
{
	add(&unumView);
	add(&vnumView);
	add(&coneView);
}

void WFConeView::onOk()
{
	WireFrameBuilder builder;
	builder.build(coneView.getValue(), unumView.getValue(), vnumView.getValue(), 10);
	IWFAddView::addWireFrame(builder.getPositions(), builder.getEdges());
}
